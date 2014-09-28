# Top-level Makefile for libcidr
# This basically calls out to various sub-level Makefiles for the build,
# and handles the bits&pieces of installing manually.

# Standard defines
.include "Makefile.inc"


# The building doesn't touch the docs, intentionally.  We presume they're
# pre-built if we care about them, because building them requires a lot
# of extra programs that many people won't have.
all build clean allclean:
	(cd src && ${MAKE} ${@})
	(cd docs && ${MAKE} ${@})
	(cd src/examples/cidrcalc && ${MAKE} ${@})


# Provide a quick&dirty 'uninstall' target
uninstall:
	@${ECHO} "-> Trying to delete everything libcidr-related..."
	${RM} ${CIDR_LIBDIR}/${SHLIB_NAME} ${CIDR_LIBDIR}/${SHLIB_LINK}
	${RM} ${CIDR_BINDIR}/cidrcalc
	${RM} ${CIDR_INCDIR}/libcidr.h
	${RM} ${CIDR_MANDIR}/man3/libcidr.3
	${RM} -r ${CIDR_DOCDIR}
	${RM} -r ${CIDR_EXDIR}
	@${ECHO} "-> Uninstallation complete"


# Now the bits of installing
install-lib:
	@${ECHO} "-> Installing ${SHLIB_NAME}..."
	-@${MKDIR} ${DESTDIR}${CIDR_LIBDIR}
	${INSTALL} -m 444 src/${SHLIB_NAME} ${DESTDIR}${CIDR_LIBDIR}/

install-cidrcalc:
	@${ECHO} "-> Installing cidrcalc..."
	-@${MKDIR} ${DESTDIR}${CIDR_BINDIR}
	${INSTALL} -m 555 src/examples/cidrcalc/cidrcalc ${DESTDIR}${CIDR_BINDIR}/

install-dev:
	@${ECHO} "-> Installing header file..."
	-@${MKDIR} ${DESTDIR}${CIDR_INCDIR}
	${INSTALL} -m 444 include/libcidr.h ${DESTDIR}${CIDR_INCDIR}/
	(cd ${DESTDIR}${CIDR_LIBDIR} && ${LN} -fs ${SHLIB_NAME} ${SHLIB_LINK})

install-man:
	@${ECHO} "-> Installing manpage..."
	( cd docs && ${MAKE} man )
	-@${MKDIR} ${DESTDIR}${CIDR_MANDIR}/man3
	${INSTALL} -m 444 docs/libcidr.3 ${DESTDIR}${CIDR_MANDIR}/man3

install-docs:
.ifndef NO_DOCS
	@${ECHO} "-> Installing docs..."
	-@${MKDIR} ${DESTDIR}${CIDR_DOCDIR}
	${INSTALL} -m 444 docs/reference/libcidr* \
			docs/reference/codelibrary-html.css ${DESTDIR}${CIDR_DOCDIR}/
.endif

install-examples:
.ifndef NO_EXAMPLES
	@${ECHO} "-> Installing examples..."
	-@${MKDIR} ${DESTDIR}${CIDR_EXDIR}
	${INSTALL} -m 444 src/examples/README ${DESTDIR}${CIDR_EXDIR}/
	@${MAKE} EX=cidrcalc install-example
	@${MAKE} EX=acl EXFILE=acl.example install-example
.endif


# Wrapup install of everything
install: install-lib install-dev install-cidrcalc \
  install-man install-docs install-examples
	@${ECHO} ""
	@${ECHO} "libcidr install complete"


# Called from install-examples above
install-example:
	@${ECHO} "-> Installing examples/${EX}..."
	-@${MKDIR} ${DESTDIR}${CIDR_EXDIR}/${EX}
	${INSTALL} -m 444 src/examples/${EX}/${EX}.c ${DESTDIR}${CIDR_EXDIR}/${EX}/
.ifdef EXFILE
	${INSTALL} -m 444 src/examples/${EX}/${EXFILE} ${DESTDIR}${CIDR_EXDIR}/${EX}/
.endif
	@${SED} \
			-e "s,%%CIDR_LIBDIR%%,${CIDR_LIBDIR}," \
			-e "s,%%CIDR_INCDIR%%,${CIDR_INCDIR}," \
			-e "s,%%PROG%%,${EX},g" \
			< src/examples/makefile.minimal \
			> ${DESTDIR}${CIDR_EXDIR}/${EX}/Makefile
