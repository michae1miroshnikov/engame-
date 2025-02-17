{ pkgs ? import <nixpkgs> {} }:
with pkgs;
mkShell {
    name = "SDL2";
    nativeBuildInputs = [
        bear
        SDL2
        SDL2_image
        SDL2_ttf
        pkg-config
    ];
    shellHook = ''
        export LD_LIBRARY_PATH=${pkgs.SDL2}/lib:${pkgs.SDL2_image}/lib:$LD_LIBRARY_PATH
        export PKG_CONFIG_PATH=${pkgs.SDL2}/lib/pkgconfig:${pkgs.SDL2_image}/lib/pkgconfig:$PKG_CONFIG_PATH
        pkg-config --cflags --libs sdl2 SDL2_image
        '';
}
