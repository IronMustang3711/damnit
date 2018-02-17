#include <Commands/Command.h>
#include <Notifier.h>
#include "profile.h"
#include <ctre/Phoenix.h>
class MotionProfileCommand2 : public frc::Command {
public:
    MotionProfileCommand2();

    static constexpr int SLOT = 0;
    static constexpr int TIMEOUT = 10;

protected:
    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End() override;

    void update();

    typedef decltype(mp::RIGHT_HOOK_TO_SCALE)::const_iterator ProfIter;

    void fill(ProfIter stopAt = mp::RIGHT_HOOK_TO_SCALE.cend());

private:
    std::unique_ptr<Notifier> notifier;
    WPI_TalonSRX *left;
    WPI_TalonSRX *right;

    ProfIter it;
};