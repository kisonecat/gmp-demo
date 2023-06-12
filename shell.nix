{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    stdenv
    gcc
    gnumake
    gmp
  ];

  shellHook = ''
    export CXXFLAGS="-I${pkgs.gmp.dev}/include"
    export LDFLAGS="-L${pkgs.gmp.dev}/lib"
  '';
}
