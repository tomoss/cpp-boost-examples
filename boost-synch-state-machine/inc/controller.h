#pragma once

#include <memory>

class Controller {
public:
    Controller();
    ~Controller() = default;
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(Controller&&) = delete;

    void activate();          // sends EvActivate
    void deactivate();        // sends EvDeactivate
    void processTask(int id); // sends EvProcess

    // Methods called by FSM actions
    void do_activate() const;
    void do_process(int id) const;
    void do_deactivate() const;

    bool can_deactivate();
private:
    struct Fsm; // Forward declaration
    std::shared_ptr<Fsm> fsm_;
};