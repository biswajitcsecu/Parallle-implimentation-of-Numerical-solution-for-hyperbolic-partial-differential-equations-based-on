#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/opt/arrayfire/lib -lCorradeInterconnect -lCorradePluginManager -lCorradeTestSuite -lCorradeUtility -lEASTL -laf -lafcpu -lafcuda -lafopencl -larmadillo -lforge -lmca_common_sm -lmca_common_verbs -lmkl_avx -lmkl_avx2 -lmkl_avx512 -lmkl_core -lmkl_def -lmkl_intel_lp64 -lmkl_mc -lmkl_mc3 -lmkl_rt -lmkl_tbb_thread -lmpi -lmpi_cxx -lmpi_mpifh -lmpi_usempi_ignore_tkr -lmpi_usempif08 -lnvrtc-builtins -lompitrace -lopen-pal -lopen-rte -lopen-trace-format -lopen-trace-format -loshmem -lotfaux -lotfaux -lsigil -ltbb -lvt-hyb -lvt-hyb -lvt-java -lvt-mpi-unify -lvt-mpi-unify -lvt-mpi -lvt-mpi -lvt-mt -lvt-mt -lvt-pomp -lvt -lvt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laxwendroffpde

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laxwendroffpde: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/laxwendroffpde ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/opt/arrayfire/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
