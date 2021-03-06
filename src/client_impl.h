/* Copyright 2017 Istio Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIXERCLIENT_CLIENT_IMPL_H
#define MIXERCLIENT_CLIENT_IMPL_H

#include "include/client.h"
#include "src/check_cache.h"
#include "src/grpc_transport.h"
#include "src/transport.h"

namespace istio {
namespace mixer_client {

class MixerClientImpl : public MixerClient {
 public:
  // Constructor
  MixerClientImpl(const MixerClientOptions& options);

  // Destructor
  virtual ~MixerClientImpl();

  virtual void Check(const Attributes& attributes, DoneFunc on_done);
  virtual void Report(const Attributes& attributes, DoneFunc on_done);
  virtual void Quota(const Attributes& attributes, DoneFunc on_done);

 private:
  MixerClientOptions options_;
  std::unique_ptr<CheckTransport> check_transport_;
  std::unique_ptr<ReportTransport> report_transport_;
  std::unique_ptr<QuotaTransport> quota_transport_;
  std::unique_ptr<GrpcTransport> grpc_transport_;

  std::shared_ptr<CheckCache> check_cache_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MixerClientImpl);
};

}  // namespace mixer_client
}  // namespace istio

#endif  // MIXERCLIENT_CLIENT_IMPL_H
