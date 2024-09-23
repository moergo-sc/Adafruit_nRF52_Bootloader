{ pkgs ? (import ./nix/pinned-nixpkgs.nix {}) }:

with pkgs;
stdenv.mkDerivation {
  name = "env";
  buildInputs = [
    gcc-arm-embedded
    (
      python3.withPackages(ps: [
        ps.intelhex
        (ps.callPackage ./nix/adafruit-nrfutil.nix {})
      ])
    )
  ];
}
