DEBCHANGE = debchange
DEBUILD = debuild
GIT = git

DEB_VERSION = 0.1~$(shell date +"%Y%m%d").git$(shell git rev-parse --short HEAD)

.PHONY: help
help:
	@echo 'Make targets:'
	@echo '  deb        - build debian package'
	@echo
	@echo 'Make variables:'
	@echo '  DEB_VERSION=$(DEB_VERSION)'

.PHONY: deb
deb:
	$(RM) -R debian
	cp -pR contrib/debian-qt5 debian
	$(DEBCHANGE) --create --package qt-emacs-key-theme -v "$(DEB_VERSION)" "New snapshot build."
	$(DEBUILD) -uc -us --build=binary
