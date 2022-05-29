{ lib, buildPythonPackage, fetchPypi
, pyserial, click, ecdsa
}:

buildPythonPackage rec {
  pname = "adafruit-nrfutil";
  version = "0.5.3.post16";

  src = fetchPypi {
    inherit version pname;
    sha256 = "1b941q13vcg31f6dy7ak2hbaq7b25ipjpz0jym8jkyahivf068dp";
  };

  propagatedBuildInputs = [
    pyserial click ecdsa
  ];

  doCheck = false;
  # doInstallCheck = false;
}
