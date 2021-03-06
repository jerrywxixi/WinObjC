//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#include <assert.h>
#include "UIProxyObject.h"
#include "UIRuntimeOutletConnection.h"
#include "UIRuntimeEventConnection.h"

UIProxyObject::UIProxyObject() {
    _identifier = NULL;
    _outputClassName = "UIProxyObject";
}

void UIProxyObject::InitFromXIB(XIBObject* obj) {
    ObjectConverter::InitFromXIB(obj);

    _identifier = obj->GetString("IBProxiedObjectIdentifier", NULL);
    _outputClassName = "UIProxyObject";
}

void UIProxyObject::InitFromStory(XIBObject* obj) {
    ObjectConverter::InitFromStory(obj);

    _identifier = obj->getAttrAndHandle("placeholderIdentifier");
    _outputClassName = "UIProxyObject";
}

void UIProxyObject::ConvertStaticMappings(NIBWriter* writer, XIBObject* obj) {
    //  Add outlets
    if (_connectedObjects) {
        for (int i = 0; i < _connectedObjects->count(); i++) {
            XIBObject* curObj = (UIRuntimeOutletConnection*)_connectedObjects->objectAtIndex(i);
            if (strcmp(curObj->_outputClassName, "UIRuntimeOutletConnection") == 0) {
                UIRuntimeOutletConnection* cur = (UIRuntimeOutletConnection*)curObj;

                UIRuntimeOutletConnection* newOutlet = new UIRuntimeOutletConnection();
                newOutlet->_label = cur->_label;
                newOutlet->_source = cur->_source;
                newOutlet->_destination = cur->_destination;
                writer->_connections->AddMember(NULL, newOutlet);
                writer->AddOutputObject(newOutlet);
            } else if (strcmp(curObj->_outputClassName, "UIRuntimeEventConnection") == 0) {
                UIRuntimeEventConnection* cur = (UIRuntimeEventConnection*)curObj;

                UIRuntimeEventConnection* newOutlet = new UIRuntimeEventConnection();
                newOutlet->_label = cur->_label;
                newOutlet->_source = cur->_source;
                newOutlet->_destination = cur->_destination;
                newOutlet->_eventMask = cur->_eventMask;
                writer->_connections->AddMember(NULL, newOutlet);
                writer->AddOutputObject(newOutlet);
            } else {
                assert(0);
            }
        }
    }
    writer->_allUIObjects->AddMember(NULL, obj);

    AddString(writer, "UIProxiedObjectIdentifier", _identifier);
    ObjectConverter::ConvertStaticMappings(writer, obj);
}
