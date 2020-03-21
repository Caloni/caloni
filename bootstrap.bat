@echo off
git submodule init
git submodule update
pushd content\post
git checkout master
popd
git clone git@github.com:Caloni/caloni.github.io.git public
pushd public
git config core.autocrlf false
popd
pushd static
git clone git@github.com:Caloni/images.git
popd
echo all good
