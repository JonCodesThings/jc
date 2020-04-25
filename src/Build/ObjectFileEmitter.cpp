#include <include/Build/ObjectFileEmitter.hpp>

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
	//surely we don't need all of this stuff????

	//set up the pass registry
	pass_registry = llvm::PassRegistry::getPassRegistry();

	//initialize some things
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmParsers();

	//initialize more things
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
	//set up the output file using the module name
	std::string outfile = module.getName();
	printf("Emitting object file for module: %s\n", outfile.c_str());

	//set up the target triple
	llvm::Triple triple;
	module.setTargetTriple(target_triple);

	//set the triple in the target triple
	triple.setTriple(llvm::sys::getDefaultTargetTriple());


	//verify the module
	if (llvm::verifyModule(module, &errs()))
	{
		printf("Module failed to verify!");
		return false;
	}

	//get the target
	std::string er;
	const Target *T = llvm::TargetRegistry::lookupTarget(triple.getTriple(), er);

	//get the cpu and feature string if needed
	std::string CPU_str = getCPUStr();
	std::string Feature_str = getFeaturesStr();

	//set the target options
	//TODO: Jon
	//figure out what stuff we actually need here
	TargetOptions Options = InitTargetOptionsFromCodeGenFlags();
	Options.DisableIntegratedAS = false;
	Options.MCOptions.ShowMCEncoding = false;
	Options.MCOptions.MCUseDwarfDirectory = false;
	Options.MCOptions.AsmVerbose = false;
	Options.MCOptions.PreserveAsmComments = true;
	Options.MCOptions.IASSearchPaths = std::vector<std::string>();
	Options.MCOptions.SplitDwarfFile = std::string();

	//set the optimizer level to default
	CodeGenOpt::Level OLvl = CodeGenOpt::None;

	//create a target machine instance
	std::unique_ptr<TargetMachine> Target(T->createTargetMachine(
		triple.getTriple(), CPU_str, Feature_str, Options, getRelocModel(),
		getCodeModel(), OLvl));

	module.setDataLayout(Target->createDataLayout());

	//create a legacy pass manager and hack together a few things
	llvm::legacy::PassManager pm;
	LLVMTargetMachine &LLVMTM = static_cast<LLVMTargetMachine &>(*Target);
	TargetPassConfig &TPC = *LLVMTM.createPassConfig(pm);
	MachineModuleInfo *MMI = new MachineModuleInfo(&LLVMTM);

	//set up up the pass manager
	std::error_code ec;
	outfile += ".o";
	llvm::raw_fd_ostream out(outfile, ec);
	TargetLibraryInfoImpl TLII(Triple(module.getTargetTriple()));
	pm.add(new TargetLibraryInfoWrapperPass(TLII));
	pm.add(MMI);
	pm.add(createPrintMIRPass(out));
	pm.add(createFreeMachineFunctionPass());

	//emit the file
	Target->addPassesToEmitFile(pm, out, nullptr, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile);
	pm.run(module);

	return true;
}
