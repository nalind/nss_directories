Name: nss_directories
Version: 0.5
Release: 1
Source: %{name}-%{version}-%{release}.tar.gz
License: LGPL
Group: System Environment/Libraries
Summary: An NSS library which searches directories.
BuildRoot: %{_tmppath}/%{name}-root

%description
Nss_directories is a set of C library extensions which allow a set of
files in a directory to be used as a primary source of groups, users,
services, and shadow passwords (instead of or in addition to using flat
files or NIS).

%prep
%setup -q -n %{name}-%{version}-%{release}
%configure --with-moduledir=/%{_lib}

%build
make

%install
rm -fr $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
install -d -m755 $RPM_BUILD_ROOT/%{_sysconfdir}/passwd.d
install -d -m755 $RPM_BUILD_ROOT/%{_sysconfdir}/shadow.d
install -d -m755 $RPM_BUILD_ROOT/%{_sysconfdir}/group.d
install -d -m755 $RPM_BUILD_ROOT/%{_sysconfdir}/protocols.d
install -d -m755 $RPM_BUILD_ROOT/%{_sysconfdir}/services.d

%clean
rm -fr $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README ChangeLog COPYING
/%{_lib}/libnss_directories-*.so
%dir %{_sysconfdir}/passwd.d
%dir %{_sysconfdir}/shadow.d
%dir %{_sysconfdir}/group.d
%dir %{_sysconfdir}/protocols.d
%dir %{_sysconfdir}/services.d

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Thu Oct 30 2003 Nalin Dahyabhai <nalin@redhat.com> 0.5-1
- include directories in the package
- be more careful to stop double-frees from overzealous applications

* Wed Oct 22 2003 Nalin Dahyabhai <nalin@redhat.com> 0.4-1
- stop referencing previously-freed memory

* Mon Nov 18 2002 Nalin Dahyabhai <nalin@redhat.com> 0.2-1
- swallow parsing functions from glibc to avoid dependencies on private symbols

* Sun Nov 17 2002 Nalin Dahyabhai <nalin@redhat.com> 0.1-1
- initial version
