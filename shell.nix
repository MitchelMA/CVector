{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "CVector";
  nativeBuildInputs = with pkgs; [
    clang
    cmake
  ];

  shellHook = ''
    export PATH=$PATH;${pkgs.clang}/bin
  '';
}
