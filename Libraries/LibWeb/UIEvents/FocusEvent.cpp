/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/FocusEventPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/UIEvents/FocusEvent.h>

namespace Web::UIEvents {

GC_DEFINE_ALLOCATOR(FocusEvent);

GC::Ref<FocusEvent> FocusEvent::create(JS::Realm& realm, FlyString const& event_name, FocusEventInit const& event_init)
{
    return realm.create<FocusEvent>(realm, event_name, event_init);
}

WebIDL::ExceptionOr<GC::Ref<FocusEvent>> FocusEvent::construct_impl(JS::Realm& realm, FlyString const& event_name, FocusEventInit const& event_init)
{
    return create(realm, event_name, event_init);
}

FocusEvent::FocusEvent(JS::Realm& realm, FlyString const& event_name, FocusEventInit const& event_init)
    : UIEvent(realm, event_name, event_init)
{
    set_related_target(const_cast<DOM::EventTarget*>(event_init.related_target.ptr()));
}

FocusEvent::~FocusEvent() = default;

void FocusEvent::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(FocusEvent);
    Base::initialize(realm);
}

}
