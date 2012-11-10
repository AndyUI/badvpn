/**
 * @file NCDRefTarget.c
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 * 
 * @section LICENSE
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <limits.h>

#include <misc/debug.h>

#include "NCDRefTarget.h"

void NCDRefTarget_Init (NCDRefTarget *o, NCDRefTarget_func_release func_release)
{
    ASSERT(func_release)
    
    o->func_release = func_release;
    o->refcnt = 1;
    
    DebugObject_Init(&o->d_obj);
}

void NCDRefTarget_Deref (NCDRefTarget *o)
{
    DebugObject_Access(&o->d_obj);
    ASSERT(o->refcnt > 0)
    
    o->refcnt--;
    
    if (o->refcnt == 0) {
        DebugObject_Free(&o->d_obj);
        o->func_release(o);
    }
}

int NCDRefTarget_Ref (NCDRefTarget *o)
{
    DebugObject_Access(&o->d_obj);
    ASSERT(o->refcnt > 0)
    
    if (o->refcnt == INT_MAX) {
        return 0;
    }
    
    o->refcnt++;
    
    return 1;
}
