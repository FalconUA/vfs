#include <string>

#include "virtualfs.h"
#include "virtualos.h"
#include "utility/shell.h"

#include "utility/ls.h"
#include "utility/cd.h"
#include "utility/pwd.h"
#include "utility/mkdir.h"
#include "utility/cat.h"
#include "utility/help.h"
#include "utility/touch.h"

int main(){
	// creating virtual operation system
	virt::operatingsystem os;

	// creating utilities
	virt::util::shell* sh_app = new virt::util::shell(&os);
	virt::util::cat* cat_app = new virt::util::cat(&os);
	virt::util::cd* cd_app = new virt::util::cd(&os);
	virt::util::ls* ls_app = new virt::util::ls(&os);
	virt::util::mkdir* mkdir_app = new virt::util::mkdir(&os);
	virt::util::pwd* pwd_app = new virt::util::pwd(&os);
	virt::util::help* help_app = new virt::util::help(&os);
	virt::util::touch* touch_app = new virt::util::touch(&os);

	// install them into our operating system
	os.install_utility("shell", static_cast<virt::os::utility*>(sh_app));
	os.install_utility("cat", static_cast<virt::os::utility*>(cat_app));
	os.install_utility("cd", static_cast<virt::os::utility*>(cd_app));
	os.install_utility("ls", static_cast<virt::os::utility*>(ls_app));
	os.install_utility("mkdir", static_cast<virt::os::utility*>(mkdir_app));
	os.install_utility("pwd", static_cast<virt::os::utility*>(pwd_app));
	os.install_utility("help", static_cast<virt::os::utility*>(help_app));
	os.install_utility("touch", static_cast<virt::os::utility*>(touch_app));

	// launch our main shell
	os.launch_utility("shell", "shell~");

	// good boys always clean their big RAM after deploying :)
	delete sh_app;
	delete cat_app;
	delete cd_app;
	delete ls_app;
	delete mkdir_app;
	delete pwd_app;
	delete help_app;
	delete touch_app;

	return 0;
}