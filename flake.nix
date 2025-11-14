{
	description = "Swallow Stars";

	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
	};

	outputs = { self, nixpkgs }:
	let
		pkgs = nixpkgs.legacyPackages.x86_64-linux;

		# Aliases
		m = pkgs.writeShellScriptBin "m" ''
			#!${pkgs.bash}/bin/bash
			make
		'';

		c = pkgs.writeShellScriptBin "c" ''
			#!${pkgs.bash}/bin/bash
			make clean
		'';

		run = pkgs.writeShellScriptBin "run" ''
			#!${pkgs.bash}/bin/bash
			./swallow-stars
		'';
		
		r = pkgs.writeShellScriptBin "a" ''
			#!${pkgs.bash}/bin/bash
			if [ -f ./swallow-stars ]; then
				make clean;
				make;
			else
				make;
			fi

			./swallow-stars
		'';
	in
	{
		devShells.x86_64-linux.default = pkgs.mkShell {
			buildInputs = with pkgs; [
				gcc gnumake ncurses

				# Aliases
				m c run r
			];
		};
	};
}
