@echo off
git clone git@github.com:Caloni/caloni.github.io.git public
pushd public
git config core.autocrlf false
popd
echo all good; type hugo to test and good luck!
