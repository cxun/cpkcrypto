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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/cpkAttributeUtil.o \
	${OBJECTDIR}/cpkDecrypt.o \
	${OBJECTDIR}/cpkDecryptUtil.o \
	${OBJECTDIR}/cpkDigest.o \
	${OBJECTDIR}/cpkDualCrypt.o \
	${OBJECTDIR}/cpkEncrypt.o \
	${OBJECTDIR}/cpkEncryptUtil.o \
	${OBJECTDIR}/cpkGeneral.o \
	${OBJECTDIR}/cpkKeys.o \
	${OBJECTDIR}/cpkObject.o \
	${OBJECTDIR}/cpkObjectUtil.o \
	${OBJECTDIR}/cpkPkcs11.o \
	${OBJECTDIR}/cpkRand.o \
	${OBJECTDIR}/cpkSession.o \
	${OBJECTDIR}/cpkSessionUtil.o \
	${OBJECTDIR}/cpkSign.o \
	${OBJECTDIR}/cpkSignUtil.o \
	${OBJECTDIR}/cpkSlotToken.o \
	${OBJECTDIR}/cpkVerify.o \
	${OBJECTDIR}/cpkVerifyUtil.o \
	${OBJECTDIR}/cpkcrypto/cpk_asn1.o \
	${OBJECTDIR}/cpkcrypto/cpk_err.o \
	${OBJECTDIR}/cpkcrypto/cpk_lib.o \
	${OBJECTDIR}/cpkcrypto/cpk_map.o \
	${OBJECTDIR}/cpkcrypto/cpk_pkcs7.o \
	${OBJECTDIR}/cpkcrypto/ecies_asn1.o \
	${OBJECTDIR}/cpkcrypto/ecies_err.o \
	${OBJECTDIR}/cpkcrypto/ecies_kdf.o \
	${OBJECTDIR}/cpkcrypto/ecies_lib.o \
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
LDLIBSOPTIONS=openssl/lib/libcrypto.a -lsocket

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpkcrypto.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpkcrypto.${CND_DLIB_EXT}: openssl/lib/libcrypto.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpkcrypto.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcpkcrypto.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/cpkAttributeUtil.o: cpkAttributeUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkAttributeUtil.o cpkAttributeUtil.c

${OBJECTDIR}/cpkDecrypt.o: cpkDecrypt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkDecrypt.o cpkDecrypt.c

${OBJECTDIR}/cpkDecryptUtil.o: cpkDecryptUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkDecryptUtil.o cpkDecryptUtil.c

${OBJECTDIR}/cpkDigest.o: cpkDigest.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkDigest.o cpkDigest.c

${OBJECTDIR}/cpkDualCrypt.o: cpkDualCrypt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkDualCrypt.o cpkDualCrypt.c

${OBJECTDIR}/cpkEncrypt.o: cpkEncrypt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkEncrypt.o cpkEncrypt.c

${OBJECTDIR}/cpkEncryptUtil.o: cpkEncryptUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkEncryptUtil.o cpkEncryptUtil.c

${OBJECTDIR}/cpkGeneral.o: cpkGeneral.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkGeneral.o cpkGeneral.c

${OBJECTDIR}/cpkKeys.o: cpkKeys.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkKeys.o cpkKeys.c

${OBJECTDIR}/cpkObject.o: cpkObject.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkObject.o cpkObject.c

${OBJECTDIR}/cpkObjectUtil.o: cpkObjectUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkObjectUtil.o cpkObjectUtil.c

${OBJECTDIR}/cpkPkcs11.o: cpkPkcs11.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkPkcs11.o cpkPkcs11.c

${OBJECTDIR}/cpkRand.o: cpkRand.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkRand.o cpkRand.c

${OBJECTDIR}/cpkSession.o: cpkSession.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkSession.o cpkSession.c

${OBJECTDIR}/cpkSessionUtil.o: cpkSessionUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkSessionUtil.o cpkSessionUtil.c

${OBJECTDIR}/cpkSign.o: cpkSign.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkSign.o cpkSign.c

${OBJECTDIR}/cpkSignUtil.o: cpkSignUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkSignUtil.o cpkSignUtil.c

${OBJECTDIR}/cpkSlotToken.o: cpkSlotToken.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkSlotToken.o cpkSlotToken.c

${OBJECTDIR}/cpkVerify.o: cpkVerify.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkVerify.o cpkVerify.c

${OBJECTDIR}/cpkVerifyUtil.o: cpkVerifyUtil.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkVerifyUtil.o cpkVerifyUtil.c

${OBJECTDIR}/cpkcrypto/cpk_asn1.o: cpkcrypto/cpk_asn1.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/cpk_asn1.o cpkcrypto/cpk_asn1.c

${OBJECTDIR}/cpkcrypto/cpk_err.o: cpkcrypto/cpk_err.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/cpk_err.o cpkcrypto/cpk_err.c

${OBJECTDIR}/cpkcrypto/cpk_lib.o: cpkcrypto/cpk_lib.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/cpk_lib.o cpkcrypto/cpk_lib.c

${OBJECTDIR}/cpkcrypto/cpk_map.o: cpkcrypto/cpk_map.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/cpk_map.o cpkcrypto/cpk_map.c

${OBJECTDIR}/cpkcrypto/cpk_pkcs7.o: cpkcrypto/cpk_pkcs7.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/cpk_pkcs7.o cpkcrypto/cpk_pkcs7.c

${OBJECTDIR}/cpkcrypto/ecies_asn1.o: cpkcrypto/ecies_asn1.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/ecies_asn1.o cpkcrypto/ecies_asn1.c

${OBJECTDIR}/cpkcrypto/ecies_err.o: cpkcrypto/ecies_err.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/ecies_err.o cpkcrypto/ecies_err.c

${OBJECTDIR}/cpkcrypto/ecies_kdf.o: cpkcrypto/ecies_kdf.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/ecies_kdf.o cpkcrypto/ecies_kdf.c

${OBJECTDIR}/cpkcrypto/ecies_lib.o: cpkcrypto/ecies_lib.c
	${MKDIR} -p ${OBJECTDIR}/cpkcrypto
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cpkcrypto/ecies_lib.o cpkcrypto/ecies_lib.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iopenssl/include -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

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
