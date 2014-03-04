##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CXml
ConfigurationName      :=Debug
WorkspacePath          := "/home/ralf/Projects/CXml"
ProjectPath            := "/home/ralf/Projects/CXml"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=ralf
Date                   :=03/04/14
CodeLitePath           :="/home/ralf/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="CXml.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lz -lm -lsqlite3
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../include/colibro/include $(IncludeSwitch)../include/colibro/extern/polarssl/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)colibro 
ArLibs                 :=  "colibro" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../include/colibro/lib $(LibraryPathSwitch)../include/colibro/extern/polarss/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/CXml$(ObjectSuffix) $(IntermediateDirectory)/examples_stupo_filme$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/CXml$(ObjectSuffix): CXml.c $(IntermediateDirectory)/CXml$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ralf/Projects/CXml/CXml.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CXml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CXml$(DependSuffix): CXml.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CXml$(ObjectSuffix) -MF$(IntermediateDirectory)/CXml$(DependSuffix) -MM "CXml.c"

$(IntermediateDirectory)/CXml$(PreprocessSuffix): CXml.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CXml$(PreprocessSuffix) "CXml.c"

$(IntermediateDirectory)/examples_stupo_filme$(ObjectSuffix): examples/stupo_filme.c $(IntermediateDirectory)/examples_stupo_filme$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/ralf/Projects/CXml/examples/stupo_filme.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/examples_stupo_filme$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/examples_stupo_filme$(DependSuffix): examples/stupo_filme.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/examples_stupo_filme$(ObjectSuffix) -MF$(IntermediateDirectory)/examples_stupo_filme$(DependSuffix) -MM "examples/stupo_filme.c"

$(IntermediateDirectory)/examples_stupo_filme$(PreprocessSuffix): examples/stupo_filme.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/examples_stupo_filme$(PreprocessSuffix) "examples/stupo_filme.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/CXml$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CXml$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CXml$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/examples_stupo_filme$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/examples_stupo_filme$(DependSuffix)
	$(RM) $(IntermediateDirectory)/examples_stupo_filme$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/CXml"


