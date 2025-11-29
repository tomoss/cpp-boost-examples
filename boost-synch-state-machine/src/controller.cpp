#include "controller.h"
#include "fsm_impl.h"

#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <unistd.h> // sleep()

namespace msm = boost::msm;

// ----------------------------------------------
// Concrete FSM Wrapper
// ----------------------------------------------
struct Controller::Fsm : public msm::back::state_machine<FSMImpl>
{
    explicit Fsm(Controller& ctrl) : msm::back::state_machine<FSMImpl>(ctrl) {}
};

Controller::Controller() : fsm_(std::make_shared<Fsm>(*this))
{

}

void Controller::activate()
{
    fsm_->process_event(EvActivate{});
}

void Controller::deactivate()
{
    fsm_->process_event(EvDeactivate{});
}

void Controller::processTask(int id)
{
    fsm_->process_event(EvProcess(id));
}

// FSM-callbacks
void Controller::do_activate() const
{
    std::cout << "Activating workflow...\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << " activate step: " << i << std::endl;
        sleep(1);
    }
}

void Controller::do_process(int id) const
{
    std::cout << "Processing task ID: " << id << std::endl;
}

bool Controller::can_deactivate()
{
    return true; // Add real validation later if needed
}

void Controller::do_deactivate() const
{
    std::cout << "Deactivating workflow...\n";

    for (int i = 0; i < 3; ++i) {
        std::cout << " deactivate step: " << i << std::endl;
        sleep(1);
    }
}