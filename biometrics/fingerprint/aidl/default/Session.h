/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <aidl/android/hardware/biometrics/fingerprint/BnSession.h>
#include <aidl/android/hardware/biometrics/fingerprint/ISessionCallback.h>

namespace aidl::android::hardware::biometrics::fingerprint {

namespace aidl::android::hardware::keymaster = keymaster;

class Session : public BnSession {
  public:
    explicit Session(std::shared_ptr<ISessionCallback> cb);

    ndk::ScopedAStatus enroll(int32_t cookie, const keymaster::HardwareAuthToken& hat,
                              std::shared_ptr<ICancellationSignal>* return_val) override;

    ndk::ScopedAStatus authenticate(int32_t cookie, int64_t keystoreOperationId,
                                    std::shared_ptr<ICancellationSignal>* return_val) override;

    ndk::ScopedAStatus detectInteraction(int32_t cookie,
                                         std::shared_ptr<ICancellationSignal>* return_val) override;

    ndk::ScopedAStatus enumerateEnrollments(int32_t cookie) override;

    ndk::ScopedAStatus removeEnrollments(int32_t cookie,
                                         const std::vector<int32_t>& enrollmentIds) override;

    ndk::ScopedAStatus getAuthenticatorId(int32_t cookie) override;

    ndk::ScopedAStatus resetLockout(int32_t cookie,
                                    const keymaster::HardwareAuthToken& hat) override;

    ndk::ScopedAStatus onPointerDown(int32_t pointerId, int32_t x, int32_t y, float minor,
                                     float major) override;

    ndk::ScopedAStatus onPointerUp(int32_t pointerId) override;

    ndk::ScopedAStatus onUiReady() override;

  private:
    std::shared_ptr<ISessionCallback> cb_;
};

}  // namespace aidl::android::hardware::biometrics::fingerprint