#pragma once

#include <iostream>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>

#include "controller.h"

namespace msmf = boost::msm::front;
namespace mpl  = boost::mpl;

// ------------------------------------
// Events
// ------------------------------------
struct EvActivate {};
struct EvDeactivate {};

struct EvProcess {
    explicit EvProcess(int id) : taskId(id) {}
    int taskId;
};


// ------------------------------------
// States
// ------------------------------------
struct Inactive   : public msmf::state<> {};
struct Active     : public msmf::state<> {};
struct Processing : public msmf::state<> {};

// ------------------------------------
// FSM Definition
// ------------------------------------

struct FSMImpl : public msmf::state_machine_def<FSMImpl>
{
    explicit FSMImpl(Controller& ctrl) : ctrl_(ctrl) {}

    typedef Inactive initial_state;

    // --------------------------------
    // Actions
    // --------------------------------
    struct ActionActivate {
        template <class FSM, class EVT, class Src, class Tgt>
        void operator()(EVT const&, FSM& fsm, Src&, Tgt&) const {
            fsm.ctrl_.do_activate();
        }
    };

    struct ActionDeactivate {
        template <class FSM, class EVT, class Src, class Tgt>
        void operator()(EVT const&, FSM& fsm, Src&, Tgt&) const {
            fsm.ctrl_.do_deactivate();
        }
    };

    struct ActionProcess {
        template <class FSM, class EVT, class Src, class Tgt>
        void operator()(EVT const& evt, FSM& fsm, Src&, Tgt&) const {
            fsm.ctrl_.do_process(evt.taskId);
        }
    };

    // --------------------------------
    // Guards
    // --------------------------------
    struct GuardCanDeactivate {
        template <class FSM, class EVT, class Src, class Tgt>
        bool operator()(EVT const&, FSM& fsm, Src&, Tgt&) const {
            return fsm.ctrl_.can_deactivate();
        }
    };

    template <class FSM>
    static const char* state_name(FSM const&, int s)
    {
        switch (s) {
        case 0: return "Inactive";
        case 1: return "Active";
        case 2: return "Processing";
        default: return "Unknown";
        }
    }

    // Called when transition does not exist
    template <class FSM, class EVT>
    void no_transition(EVT const& e, FSM& fsm, int state)
    {
        std::cerr << "[FSM] No transition from state "
                  << state_name(fsm, state)
                  << " on event " << typeid(e).name()
                  << std::endl;
    }

    // --------------------------------
    // Transition Table
    // --------------------------------
    struct transition_table : mpl::vector<
        //          Start       Event         Next        Action            Guard
        msmf::Row< Inactive,   EvActivate,   Active,     ActionActivate,   msmf::none >,
        msmf::Row< Active,     EvDeactivate, Inactive,   ActionDeactivate, GuardCanDeactivate >,
        // In Active, we can process tasks
        msmf::Row< Active,     EvProcess,    Processing, ActionProcess,    msmf::none >,
        // After processing a task, return to Active
        msmf::Row< Processing, EvDeactivate, Inactive,   ActionDeactivate, GuardCanDeactivate >
    > 
    {};

    Controller& ctrl_;
};