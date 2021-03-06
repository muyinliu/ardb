/*
 *Copyright (c) 2013-2016, yinqiwen <yinqiwen@gmail.com>
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Redis nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 *BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DB_UTILS_HPP_
#define DB_UTILS_HPP_

#include "common/common.hpp"
#include "codec.hpp"
#include "thread/thread_local.hpp"
#include "thread/thread_mutex_lock.hpp"
#include "thread/spin_rwlock.hpp"
#include "thread/event_condition.hpp"
#include "util/concurrent_queue.hpp"
OP_NAMESPACE_BEGIN

    struct DBLocalContext
    {
            Buffer encode_buffer_cache;
            std::string string_cache;
            Buffer& GetEncodeBuferCache()
            {
                encode_buffer_cache.Clear();
                return encode_buffer_cache;
            }
            Slice GetSlice(const KeyObject& key);
            void GetSlices(const KeyObject& key, const ValueObject& val, Slice ss[2]);
            std::string& GetStringCache()
            {
                string_cache.clear();
                return string_cache;
            }
            virtual ~DBLocalContext()
            {
            }
    };

    class DBHelper
    {
        public:
            /*
             * Some engine need all names before open,
             * we need to persist the names
             */
            static int ListNameSpaces(DataArray& nss);
            static int AddNameSpace(const Data& ns);
            static int DelNamespace(const Data& ns);
    };
OP_NAMESPACE_END

#endif /* SRC_DB_DB_UTILS_HPP_ */
