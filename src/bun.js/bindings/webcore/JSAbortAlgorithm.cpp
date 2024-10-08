/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSAbortAlgorithm.h"

#include "JSDOMConvertBase.h"
#include "JSDOMExceptionHandling.h"
#include "ScriptExecutionContext.h"
#include "DeleteCallbackDataTask.h"

namespace WebCore {
using namespace JSC;

JSAbortAlgorithm::JSAbortAlgorithm(VM& vm, JSObject* callback)
    : AbortAlgorithm(jsCast<JSDOMGlobalObject*>(callback->globalObject())->scriptExecutionContext())
    , m_data(new JSCallbackDataStrong(vm, callback, this))
{
}

JSAbortAlgorithm::~JSAbortAlgorithm()
{
    ScriptExecutionContext* context = scriptExecutionContext();
    // When the context is destroyed, all tasks with a reference to a callback
    // should be deleted. So if the context is 0, we are on the context thread.
    if (!context || context->isContextThread())
        delete m_data;
    else

        context->postTask(new DeleteCallbackDataTask(m_data));
#ifndef NDEBUG
    m_data = nullptr;
#endif
}

CallbackResult<typename IDLUndefined::ImplementationType> JSAbortAlgorithm::handleEvent(JSValue value)
{
    if (!canInvokeCallback())
        return CallbackResultType::UnableToExecute;

    Ref<JSAbortAlgorithm> protectedThis(*this);

    auto& globalObject = *jsCast<JSDOMGlobalObject*>(m_data->callback()->globalObject());
    auto& vm = globalObject.vm();

    JSLockHolder lock(vm);
    auto& lexicalGlobalObject = globalObject;
    JSValue thisValue = jsUndefined();
    MarkedArgumentBuffer args;
    args.append(value);
    ASSERT(!args.hasOverflowed());

    NakedPtr<JSC::Exception> returnedException;
    m_data->invokeCallback(vm, thisValue, args, JSCallbackData::CallbackType::Function, Identifier(), returnedException);
    if (returnedException) {
        reportException(&lexicalGlobalObject, returnedException);
        return CallbackResultType::ExceptionThrown;
    }

    return {};
}

JSC::JSValue toJS(AbortAlgorithm& impl)
{
    if (!static_cast<JSAbortAlgorithm&>(impl).callbackData())
        return jsNull();

    return static_cast<JSAbortAlgorithm&>(impl).callbackData()->callback();
}

} // namespace WebCore
