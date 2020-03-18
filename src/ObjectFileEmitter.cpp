#include <include/ObjectFileEmitter.hpp>

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/CodeGen/CommandFlags.inc"
#include "llvm/CodeGen/LinkAllAsmWriterComponents.h"
#include "llvm/CodeGen/LinkAllCodegenComponents.h"
#include "llvm/CodeGen/MIRParser/MIRParser.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/AutoUpgrade.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/RemarkStreamer.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/MC/SubtargetFeature.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/PluginLoader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/WithColor.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/Utils/Cloning.h"

ObjectFileEmitter::ObjectFileEmitter(llvm::LLVMContext &context) : context(context) {}

ObjectFileEmitter::~ObjectFileEmitter() {}

void ObjectFileEmitter::Initialize()
{
	pass_registry = llvm::PassRegistry::getPassRegistry();

	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmParsers();

	llvm::initializeCore(*pass_registry);
	llvm::initializeCodeGen(*pass_registry);
	llvm::initializeLoopStrengthReducePass(*pass_registry);
	llvm::initializeLowerIntrinsicsPass(*pass_registry);
	llvm::initializeEntryExitInstrumenterPass(*pass_registry);
	llvm::initializePostInlineEntryExitInstrumenterPass(*pass_registry);
	llvm::initializeUnreachableBlockElimLegacyPassPass(*pass_registry);
	llvm::initializeConstantHoistingLegacyPassPass(*pass_registry);
	llvm::initializeScalarOpts(*pass_registry);
	llvm::initializeVectorization(*pass_registry);
	llvm::initializeScalarizeMaskedMemIntrinPass(*pass_registry);
	llvm::initializeExpandReductionsPass(*pass_registry);
	llvm::initializeHardwareLoopsPass(*pass_registry);
}

bool ObjectFileEmitter::EmitObjectFile(llvm::Module & module)
{
	std::string outfile = module.getName();
	printf("Emitting object file for module: %s\n", outfile.c_str());

	llvm::Triple triple;
	module.setTargetTriple(target_triple);

	triple.setTriple(llvm::sys::getDefaultTargetTriple());

	std::string er;
	const Target *T = llvm::TargetRegistry::lookupTarget(triple.getTriple(), er);

	std::string CPU_str = getCPUStr();
	std::string Feature_str = getFeaturesStr();

	TargetOptions Options = InitTargetOptionsFromCodeGenFlags();
	Options.DisableIntegratedAS = false;
	Options.MCOptions.ShowMCEncoding = false;
	Options.MCOptions.MCUseDwarfDirectory = false;
	Options.MCOptions.AsmVerbose = false;
	Options.MCOptions.PreserveAsmComments = true;
	Options.MCOptions.IASSearchPaths = std::vector<std::string>();
	Options.MCOptions.SplitDwarfFile = std::string();

	CodeGenOpt::Level OLvl = CodeGenOpt::Default;

	std::unique_ptr<TargetMachine> Target(T->createTargetMachine(
		triple.getTriple(), CPU_str, Feature_str, Options, getRelocModel(),
		getCodeModel(), OLvl));

	if (llvm::verifyModule(module, &errs()))
		printf("Module failed to verify!");

	llvm::legacy::PassManager pm;
	LLVMTargetMachine &LLVMTM = static_cast<LLVMTargetMachine &>(*Target);
	TargetPassConfig &TPC = *LLVMTM.createPassConfig(pm);
	MachineModuleInfo *MMI = new MachineModuleInfo(&LLVMTM);


	std::error_code ec;
	outfile += ".o";
	llvm::raw_fd_ostream out(outfile, ec);
	TargetLibraryInfoImpl TLII(Triple(module.getTargetTriple()));
	pm.add(new TargetLibraryInfoWrapperPass(TLII));
	pm.add(MMI);

	pm.add(createPrintMIRPass(out));
	pm.add(createFreeMachineFunctionPass());

	Target->addPassesToEmitFile(pm, out, nullptr, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile);
	pm.run(module);

	return true;
}
