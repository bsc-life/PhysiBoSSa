#include "MaBoSSCellCycleNetwork.h"

CellCycleNetwork::CellCycleNetwork(std::string bnd_file, std::string cfg_file)
{
	this->maboss = new MaBoSSNetwork(bnd_file, cfg_file);

	// initialize all nodes to 0
	this->nodes.resize( maboss->nodes_lenght() );
	this->maboss->recover_state(&(this->nodes));

	this->set_time_to_update();
}

CellCycleNetwork::~CellCycleNetwork()
{
	delete this->maboss;
	this->maboss = NULL;
}

/* random update time, to asynchronize it between all cells */
void CellCycleNetwork::set_time_to_update()
{
	this->time_to_update = (1 + 0.5*UniformRandom11()) * this->maboss->get_update_time_step();
}

/* Update MaboSS network states */
void CellCycleNetwork::run_maboss()
{
	this->maboss->run(&this->nodes);
	this->set_time_to_update();
}