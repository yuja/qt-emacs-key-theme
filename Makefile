DEBCHANGE = debchange
DEBUILD = debuild
GIT = git
QMAKE = qmake

DEB_VERSION = 0.1~$(shell date +"%Y%m%d").git$(shell git rev-parse --short HEAD)
QT_VERSION_MAJOR = $(word 1,$(subst ., ,$(shell $(QMAKE) -query QT_VERSION)))

.PHONY: help
help:
	@echo 'Make targets:'
	@echo '  deb        - build debian package'
	@echo
	@echo 'Make variables:'
	@echo '  DEB_VERSION=$(DEB_VERSION)'
	@echo '  QT_VERSION_MAJOR=$(QT_VERSION_MAJOR)'

.PHONY: deb
deb:
	$(RM) -R debian
	cp -pR "contrib/debian-qt$(QT_VERSION_MAJOR)" debian
	$(DEBCHANGE) --create --package "qt$(QT_VERSION_MAJOR)-emacs-key-theme" \
		-v "$(DEB_VERSION)" "New snapshot build."
	$(DEBUILD) -uc -us --build=binary
