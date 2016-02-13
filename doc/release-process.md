Release Process
====================

* update translations (ping wumpus, Diapolo or tcatm on IRC)
* see https://github.com/bitcoin/bitcoin/blob/master/doc/translation_process.md#syncing-with-transifex

* * *

###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

###update gitian

 In order to take advantage of the new caching features in gitian, be sure to update to a recent version (`e9741525c` or later is recommended)

<<<<<<< HEAD
=======
###perform gitian builds

>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
 From a directory containing the dogecoin source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./dogecoin
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder

<<<<<<< HEAD
 Fetch and build inputs: (first time, or when dependency versions change)

	mkdir -p inputs; cd inputs/
	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20140701.tar.gz' -O miniupnpc-1.9.20140701.tar.gz
	wget 'https://www.openssl.org/source/openssl-1.0.1l.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-5.1.29.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'https://downloads.sourceforge.net/project/libpng/libpng16/older-releases/1.6.8/libpng-1.6.8.tar.gz'
	wget 'https://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'https://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'https://svn.boost.org/trac/boost/raw-attachment/ticket/7262/boost-mingw.patch' -O \
	     boost-mingw-gas-cross-compile-2013-03-03.patch
	wget 'https://download.qt-project.org/official_releases/qt/5.2/5.2.0/single/qt-everywhere-opensource-src-5.2.0.tar.gz'
	wget 'https://download.qt-project.org/archive/qt/4.6/qt-everywhere-opensource-src-4.6.4.tar.gz'
	wget 'https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.bz2'
	cd ..
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/boost-linux.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/deps-linux.yml
	mv build/out/dogecoin-deps-*.zip inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/qt-linux.yml
	mv build/out/qt-*.tar.gz inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/boost-win.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/deps-win.yml
	mv build/out/dogecoin-deps-*.zip inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/qt-win.yml
	mv build/out/qt-*.zip inputs/
	./bin/gbuild ../dogecoin/contrib/gitian-descriptors/protobuf-win.yml
	mv build/out/protobuf-*.zip inputs/

 The expected SHA256 hashes of the intermediate inputs are:

    0331de2b05c275986545e8d2d6a4becf625e5935034803dc508c9d641e70c7cb  dogecoin-deps-linux32-gitian-r10.zip
    d99caabf13011494dd147b4ffad1626480889f5080270a1a04e1a7adc543cc4f  dogecoin-deps-linux64-gitian-r10.zip
    f29b7d9577417333fb56e023c2977f5726a7c297f320b175a4108cf7cd4c2d29  boost-linux32-1.55.0-gitian-r1.zip
    88232451c4104f7eb16e469ac6474fd1231bd485687253f7b2bdf46c0781d535  boost-linux64-1.55.0-gitian-r1.zip
    57e57dbdadc818cd270e7e00500a5e1085b3bcbdef69a885f0fb7573a8d987e1  qt-linux32-4.6.4-gitian-r1.tar.gz
    60eb4b9c5779580b7d66529efa5b2836ba1a70edde2a0f3f696d647906a826be  qt-linux64-4.6.4-gitian-r1.tar.gz
    60dc2d3b61e9c7d5dbe2f90d5955772ad748a47918ff2d8b74e8db9b1b91c909  boost-win32-1.55.0-gitian-r6.zip
    f65fcaf346bc7b73bc8db3a8614f4f6bee2f61fcbe495e9881133a7c2612a167  boost-win64-1.55.0-gitian-r6.zip
    3783d98ac49256f11381d4eadffed5b51c1779afedca43ffef6cf8998d1db9c5  dogecoin-deps-win32-gitian-r17.zip
    b579a9af8a8b77d542738cf93e5a12bfb0957dade0281bebd96a1619fc587855  dogecoin-deps-win64-gitian-r17.zip
    963e3e5e85879010a91143c90a711a5d1d5aba992e38672cdf7b54e42c56b2f1  qt-win32-5.2.0-gitian-r3.zip
    751c579830d173ef3e6f194e83d18b92ebef6df03289db13ab77a52b6bc86ef0  qt-win64-5.2.0-gitian-r3.zip
    e2e403e1a08869c7eed4d4293bce13d51ec6a63592918b90ae215a0eceb44cb4  protobuf-win32-2.5.0-gitian-r4.zip
    a0999037e8b0ef9ade13efd88fee261ba401f5ca910068b7e0cd3262ba667db0  protobuf-win64-2.5.0-gitian-r4.zip

 Build dogecoind and dogecoin-qt on Linux32, Linux64, and Win32:
  
	./bin/gbuild --commit dogecoin=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION} --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-linux.yml
	pushd build/out
	zip -r dogecoin-${VERSION}-linux-gitian.zip *
	mv dogecoin-${VERSION}-linux-gitian.zip ../../../
	popd
	./bin/gbuild --commit dogecoin=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-win.yml
	pushd build/out
	zip -r dogecoin-${VERSION}-win-gitian.zip *
	mv dogecoin-${VERSION}-win-gitian.zip ../../../
	popd
	popd
=======
###fetch and build inputs: (first time, or when dependency versions change)
 
	mkdir -p inputs
	wget -P inputs https://bitcoincore.org/cfields/osslsigncode-Backports-to-1.7.1.patch
	wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

 Register and download the Apple SDK: (see OSX Readme for details)
 
 https://developer.apple.com/devcenter/download.action?path=/Developer_Tools/xcode_6.1.1/xcode_6.1.1.dmg
 
 Using a Mac, create a tarball for the 10.9 SDK and copy it to the inputs directory:
 
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.9.sdk.tar.gz MacOSX10.9.sdk

<<<<<<< HEAD
  1. linux 32-bit and 64-bit binaries + source (dogecoin-${VERSION}-linux-gitian.zip)
  2. windows 32-bit and 64-bit binaries + installer + source (dogecoin-${VERSION}-win-gitian.zip)
  3. Gitian signatures (in gitian.sigs/${VERSION}[-win]/(your gitian key)/
=======
###Optional: Seed the Gitian sources cache
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

  By default, gitian will fetch source files as needed. For offline builds, they can be fetched ahead of time:

	make -C ../dogecoin/depends download SOURCES_PATH=`pwd`/cache/common

<<<<<<< HEAD
	unzip dogecoin-${VERSION}-linux-gitian.zip -d dogecoin-${VERSION}-linux
	tar czvf dogecoin-${VERSION}-linux.tar.gz dogecoin-${VERSION}-linux
	rm -rf dogecoin-${VERSION}-linux

**Windows .zip and setup.exe:**

	unzip dogecoin-${VERSION}-win-gitian.zip -d dogecoin-${VERSION}-win
	mv dogecoin-${VERSION}-win/dogecoin-*-setup.exe .
	zip -r dogecoin-${VERSION}-win.zip dogecoin-${VERSION}-win
	rm -rf dogecoin-${VERSION}-win

**Perform Mac build:**

  OSX binaries are created by Gavin Andresen on a 64-bit, OSX 10.6 machine.

	./autogen.sh
        SDK=$(xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.6.sdk
        CXXFLAGS="-mmacosx-version-min=10.6 -isysroot $SDK" ./configure --enable-upnp-default
	make
	export QTDIR=/opt/local/share/qt4  # needed to find translations/qt_*.qm files
	T=$(contrib/qt_translations.py $QTDIR/translations src/qt/locale)
        export CODESIGNARGS='--keychain ...path_to_keychain --sign "Developer ID Application: DOGECOIN FOUNDATION, INC., THE"'
	python2.7 contrib/macdeploy/macdeployqtplus Dogecoin-Qt.app -sign -add-qt-tr $T -dmg -fancy contrib/macdeploy/fancy.plist

 Build output expected: Dogecoin-Qt.dmg
=======
  Only missing files will be fetched, so this is safe to re-run for each build.

###Build Dogecoin Core for Linux, Windows, and OS X:
  
	./bin/gbuild --commit dogecoin=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-linux.yml
	mv build/out/dogecoin-*.tar.gz build/out/src/dogecoin-*.tar.gz ../
	./bin/gbuild --commit dogecoin=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-win.yml
	mv build/out/dogecoin-*-win-unsigned.tar.gz inputs/dogecoin-win-unsigned.tar.gz
	mv build/out/dogecoin-*.zip build/out/dogecoin-*.exe ../
	./bin/gbuild --commit dogecoin=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-osx.yml
	mv build/out/dogecoin-*-osx-unsigned.tar.gz inputs/dogecoin-osx-unsigned.tar.gz
	mv build/out/dogecoin-*.tar.gz build/out/dogecoin-*.dmg ../
	popd
  Build output expected:

  1. source tarball (dogecoin-${VERSION}.tar.gz)
  2. linux 32-bit and 64-bit dist tarballs (dogecoin-${VERSION}-linux[32|64].tar.gz)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (dogecoin-${VERSION}-win[32|64]-setup-unsigned.exe, dogecoin-${VERSION}-win[32|64].zip)
  4. OSX unsigned installer and dist tarball (dogecoin-${VERSION}-osx-unsigned.dmg, dogecoin-${VERSION}-osx64.tar.gz)
  5. Gitian signatures (in gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your gitian key)/
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win-unsigned/${SIGNER}
	git add ${VERSION}-osx-unsigned/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

  Wait for Windows/OSX detached signatures:
	Once the Windows/OSX builds each have 3 matching signatures, they will be signed with their respective release keys.
	Detached signatures will then be committed to the dogecoin-detached-sigs repository, which can be combined with the unsigned apps to create signed binaries.

<<<<<<< HEAD
* update dogecoin.com version
  make sure all OS download links go to the right versions
  
* update forum version
=======
  Create the signed OSX binary:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	mv build/out/dogecoin-osx-signed.dmg ../dogecoin-${VERSION}-osx.dmg
	popd
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

  Create the signed Windows binaries:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../dogecoin/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../dogecoin/contrib/gitian-descriptors/gitian-win-signer.yml
	mv build/out/dogecoin-*win64-setup.exe ../dogecoin-${VERSION}-win64-setup.exe
	mv build/out/dogecoin-*win32-setup.exe ../dogecoin-${VERSION}-win32-setup.exe
	popd

Commit your signature for the signed OSX/Windows binaries:

	pushd gitian.sigs
<<<<<<< HEAD
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git add ${VERSION}-osx/${SIGNER}
=======
	git add ${VERSION}-osx-signed/${SIGNER}
	git add ${VERSION}-win-signed/${SIGNER}
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

<<<<<<< HEAD
From a directory containing dogecoin source, gitian.sigs and gitian zips

	export VERSION=(new version, e.g. 0.8.0)
	mkdir dogecoin-${VERSION}-linux-gitian
	pushd dogecoin-${VERSION}-linux-gitian
	unzip ../dogecoin-${VERSION}-linux-gitian.zip
	mkdir gitian
	cp ../dogecoin/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}/); do
	 cp ../gitian.sigs/${VERSION}/${signer}/dogecoin-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}/${signer}/dogecoin-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r dogecoin-${VERSION}-linux-gitian.zip *
	cp dogecoin-${VERSION}-linux-gitian.zip ../
	popd
	mkdir dogecoin-${VERSION}-win-gitian
	pushd dogecoin-${VERSION}-win-gitian
	unzip ../dogecoin-${VERSION}-win-gitian.zip
	mkdir gitian
	cp ../dogecoin/contrib/gitian-downloader/*.pgp ./gitian/
	for signer in $(ls ../gitian.sigs/${VERSION}-win/); do
	 cp ../gitian.sigs/${VERSION}-win/${signer}/dogecoin-build.assert ./gitian/${signer}-build.assert
	 cp ../gitian.sigs/${VERSION}-win/${signer}/dogecoin-build.assert.sig ./gitian/${signer}-build.assert.sig
	done
	zip -r dogecoin-${VERSION}-win-gitian.zip *
	cp dogecoin-${VERSION}-win-gitian.zip ../
	popd

    - Code-sign MacOSX .dmg

  Note: only Gavin has the code-signing keys currently.

- Create `SHA256SUMS.asc` for builds, and PGP-sign it. This is done manually.
  Include all the files to be uploaded. The file has `sha256sum` format with a
  simple header at the top:

```
Hash: SHA256

0060f7d38b98113ab912d4c184000291d7f026eaf77ca5830deec15059678f54  bitcoin-x.y.z-linux.tar.gz
...
```

- Upload gitian zips to SourceForge

- Announce the release:

  - Add the release to dogecoin.com

  - Announce on reddit /r/dogecoin, /r/dogecoindev

  - Release sticky on discuss dogecoin: https://discuss.dogecoin.com/categories/announcements
=======
- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:
```bash
sha256sum * > SHA256SUMS
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the dogecoin.com Github repo

- Update dogecoin.com version - Langerhans to do

- Announce the release:

  - Release sticky on Dogecoin Forums: http://forum.dogecoin.com/forum/news-community/community-announcements

  - Dogecoin-development mailing list

  - Update title of #dogecoin on Freenode IRC

  - Announce on reddit /r/dogecoin, /r/dogecoindev

- Add release notes for the new version to the directory `doc/release-notes` in git master
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

- To the moon!
