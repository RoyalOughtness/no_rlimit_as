Name:           no_rlimit_as
Version:        0.2.0
Release:        1
Summary:        Shared library that can be preloaded to disable setrlimit(RLIMIT_AS).

License:        MIT
URL:            https://github.com/HastD/%{name}
Source0:        https://github.com/HastD/%{name}/archive/refs/tags/v%{version}.tar.gz

BuildRequires:  meson
BuildRequires:  gcc

%description
%{name} is a shared library that, when preloaded, modifies the C standard
library function `setrlimit` to make it a no-op when called with `RLIMIT_AS`.
The Linux-specific function `prlimit` and the variants `setrlimit64` and
`prlimit64` are similarly modified.

%prep
%autosetup

%build
%meson
%meson_build

%install
%meson_install

%post -p /usr/bin/ldconfig
%postun -p /usr/bin/ldconfig

%files
%{_libdir}/lib%{name}.so

%changelog
* Sun Oct 19 2025 Daniel Hast <hast.daniel@protonmail.com> v0.1.0
  - Initial RPM release.
