#pragma once
#ifndef __BIBIM_UI_H__
#define __BIBIM_UI_H__

#   include <Bibim/UIDomain.h>
#       include <Bibim/UISimpleDomain.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/UIImage.h>
#   include <Bibim/UIMarkupText.h>
#   include <Bibim/UIRenderer.h>
#   include <Bibim/UIVisualVisitor.h>
#       include <Bibim/UIDrawingContext.h>
#           include <Bibim/UIHandledDrawingContext.h>
#       include <Bibim/UIPickingContext.h>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Frames
#       include <Bibim/UIFrame.h>
#           include <Bibim/UIAlignedFrame.h>
#           include <Bibim/UIAnchoredFrame.h>
#           include <Bibim/UIFittedFrame.h>
#           include <Bibim/UIFixedFrame.h>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Effects
#       include <Bibim/UIEffect.h>
#           include <Bibim/UITintEffect.h>
#       include <Bibim/UIEffectMap.h>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Events
#       include <Bibim/UIAsyncEventQueue.h>
#       include <Bibim/UIEventArgs.h>
#           include <Bibim/UIGamePadEventArgs.h>
#           include <Bibim/UIKeyboardEventArgs.h>
#           include <Bibim/UIMouseEventArgs.h>
#               include <Bibim/UIMouseButtonEventArgs.h>
#               include <Bibim/UIMouseWheelEventArgs.h>
#           include <Bibim/UITouchEventArgs.h>
#       include <Bibim/UIEventDispatcher.h>
#           include <Bibim/UIAppEventDispatcher.h>
#           include <Bibim/UIGamePadEventDispatcher.h>
#           include <Bibim/UIKeyboardEventDispatcher.h>
#           include <Bibim/UIMouseEventDispatcher.h>
#           include <Bibim/UITouchEventDispatcher.h>
#       include <Bibim/UIEventID.h>
#       include <Bibim/UIEventMap.h>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Transforms
#       include <Bibim/UITransform.h>
#           include <Bibim/UITransform3D.h>
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Visuals
#       include <Bibim/UIVisual.h>
#           include <Bibim/UILabel.h>
#           include <Bibim/UIPanel.h>
#               include <Bibim/UIButton.h>
#                   include <Bibim/UICheckBox.h>
#               include <Bibim/UIEditBox.h>
#               include <Bibim/UIFlowPanel.h>
#                   include <Bibim/UIListBox.h>
#               include <Bibim/UIMarkupTextBox.h>
#               include <Bibim/UIWindow.h>
#           include <Bibim/UISprite.h>
#           include <Bibim/UIVideo.h>

#endif