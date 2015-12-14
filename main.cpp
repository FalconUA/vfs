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
#include "utility/rm.h"
#include "utility/mv.h"
#include "utility/cp.h"

// We are too lazy to implement the input/output to physical drive.
#include "lazy_initialize.h"

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
	virt::util::rm* rm_app = new virt::util::rm(&os);
	virt::util::mv* mv_app = new virt::util::mv(&os);
	virt::util::cp* cp_app = new virt::util::cp(&os);

	// install them into our operating system
	os.install_utility("shell", static_cast<virt::os::utility*>(sh_app));
	os.install_utility("cat", static_cast<virt::os::utility*>(cat_app));
	os.install_utility("cd", static_cast<virt::os::utility*>(cd_app));
	os.install_utility("ls", static_cast<virt::os::utility*>(ls_app));
	os.install_utility("mkdir", static_cast<virt::os::utility*>(mkdir_app));
	os.install_utility("pwd", static_cast<virt::os::utility*>(pwd_app));
	os.install_utility("help", static_cast<virt::os::utility*>(help_app));
	os.install_utility("touch", static_cast<virt::os::utility*>(touch_app));
	os.install_utility("rm", static_cast<virt::os::utility*>(rm_app));
	os.install_utility("mv", static_cast<virt::os::utility*>(mv_app));
	os.install_utility("cp", static_cast<virt::os::utility*>(cp_app));

	// launch our main shell
	sample_filesystem(os);
	os.launch_utility("shell", "default shell");

	// good boys always clean their big RAM after deploying :)
	delete sh_app;
	delete cat_app;
	delete cd_app;
	delete ls_app;
	delete mkdir_app;
	delete pwd_app;
	delete help_app;
	delete touch_app;
	delete rm_app;
	delete mv_app;
	delete cp_app;

	return 0;
}
