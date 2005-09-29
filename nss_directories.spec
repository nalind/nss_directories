Name: nss_directories
Version: 0.6
Release: 2
Source: %{name}-%{version}.tar.gz
License: LGPL
Group: System Environment/Libraries
Summary: An NSS library which searches directories containing multiple files
BuildRoot: %{_tmppath}/%{name}-root

%description
The nss_directories module is a set of C library extensions which
allow a set of files in a directory to be used as a primary source of
groups, users, services, and shadow passwords (instead of or in
addition to using flat files or NIS).

%prep
%setup -q
%configure --libdir=/%{_lib}

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
rm $RPM_BUILD_ROOT/%{_lib}/*.so
rm $RPM_BUILD_ROOT/%{_lib}/*.a
rm $RPM_BUILD_ROOT/%{_lib}/*.la

touch $RPM_BUILD_ROOT/topdir
install -d -m755 $RPM_BUILD_ROOT/%{_libdir}/
topdir=
while ! test -f $RPM_BUILD_ROOT/%{_libdir}/$topdir/topdir ; do
	topdir=..${topdir:+/${topdir}}
done
pushd $RPM_BUILD_ROOT/%{_libdir}
ln -sf ${topdir}/%{_lib}/libnss_directories.so.? libnss_directories.so
popd
rm -f $RPM_BUILD_ROOT/topdir

%clean
rm -fr $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README ChangeLog COPYING
/%{_lib}/libnss_directories*
%{_libdir}/libnss_directories.so
%dir %{_sysconfdir}/passwd.d
%dir %{_sysconfdir}/shadow.d
%dir %{_sysconfdir}/group.d
%dir %{_sysconfdir}/protocols.d
%dir %{_sysconfdir}/services.d

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Thu Sep 29 2005 Nalin Dahyabhai <nalin@redhat.com> 0.6-2
- clean up symlinks

* Thu Mar 17 2005 Nalin Dahyabhai <nalin@redhat.com> 0.6-1
- fix a referring-to-freed-memory bug
- update autotools machinery

* Thu Oct 30 2003 Nalin Dahyabhai <nalin@redhat.com> 0.5-1
- include directories in the package
- be more careful to stop double-frees from overzealous applications

* Wed Oct 22 2003 Nalin Dahyabhai <nalin@redhat.com> 0.4-1
- stop referencing previously-freed memory

* Mon Nov 18 2002 Nalin Dahyabhai <nalin@redhat.com> 0.2-1
- swallow parsing functions from glibc to avoid dependencies on private symbols

* Sun Nov 17 2002 Nalin Dahyabhai <nalin@redhat.com> 0.1-1
- initial version
