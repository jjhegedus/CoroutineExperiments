#include "Resumable1.h"





bool Resumable1::awaiter::await_ready() const noexcept {
    return m_resumable1.isSet();
}