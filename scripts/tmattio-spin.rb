class TmattioSpin < Formula
  VERSION = '0.4.8'
  desc 'Project scaffolding tool and set of templates for Reason and OCaml.'
  homepage 'https://github.com/tmattio/spin'
  url "https://github.com/tmattio/spin/releases/download/v#{VERSION}/spin-darwin-x64.zip"
  version VERSION

  bottle :unneeded

  test do
    system "#{bin}/spin", '--version'
  end

  def install
    mv "spin.exe", "spin"
    bin.install 'spin'
  end
end
