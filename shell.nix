with (import <nixpkgs> {});

stdenv.mkDerivation {
  name = "env";
  buildInputs = [
    # pkgsCross.arm-embedded.buildPackages.gcc
    # pkgsCross.arm-embedded.buildPackages.binutils
    gcc-arm-embedded

    (
      python37.withPackages(ps: [
        ps.intelhex
        (ps.callPackage ./nix/adafruit-nrfutil.nix {})
      ])
    )
  ];
}
