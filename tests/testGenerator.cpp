#include <viewer/Viewer.h>
#include <enki/PhysicalEngine.h>
#include <QApplication>
#include <enki/worldgenerator/WorldGenerator.h>

using namespace Enki;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	WorldGenerator* gen = new WorldGenerator();

	gen->add(Factory::PHYS_OBJ, 10);
	gen->add(Factory::THYMIO2, 10);
	gen->add(Factory::EPUCK, 10);
	gen->add(Factory::SBOT, 10);
	gen->add(Factory::KHEPERA, 10);
	gen->add(Factory::MARXBOT, 10);

	//gen->add(WG_ROBOTS, 10);
	//gen->add(WG_ANYTHING, 10);

	ViewerWidget* viewer = new ViewerWidget(gen->getWorld(), 0);
	viewer->show();
	return app.exec();
}
