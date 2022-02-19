DEBCHANGE = debchange
DEBUILD = debuild
GIT = git

DEBVERSION = 0.1~$(shell date +"%Y%m%d").git$(shell git rev-parse --short HEAD)

.PHONY: help
help:
	@echo 'Make targets:'
	@echo '  deb        - build debian package'
	@echo
	@echo 'Make variables:'
	@echo '  DEBVERSION=$(DEBVERSION)'

.PHONY: deb
deb:
	cp debian/changelog.release debian/changelog
	$(DEBCHANGE) -v "$(DEBVERSION)" "New snapshot build."
	$(DEBUILD) -uc -us
