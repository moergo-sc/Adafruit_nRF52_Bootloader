with (import <nixpkgs> {});

stdenv.mkDerivation {
  name = "env";
  buildInputs = [
    gcc-arm-embedded

    (
      python37.withPackages(ps: [
        ps.intelhex
        (ps.callPackage ./nix/adafruit-nrfutil.nix {})
      ])
    )
  ];
}
