with (import <nixpkgs> {});

stdenv.mkDerivation {
  name = "env";
  buildInputs = [
    gcc-arm-embedded

    (
      python38.withPackages(ps: [
        ps.intelhex
        (ps.callPackage ./nix/adafruit-nrfutil.nix {})
      ])
    )
  ];
}
