/*
-----------------------------------------------------------------------------
This source file is part of Indigente Game Engine
Indigente - Interactive Digital Entertainment
For the latest info, see http://indigente.dcc.ufba.br

Copyright  2004-2006 Indigente


This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef __InGE_H__
#define __InGE_H__

#include "Audio/AudioManager.h"
#include "Audio/AudioBuffer.h"
#include "Audio/AudioListener.h"
#include "Audio/AudioSource.h"

#include "Common/SceneManager.h"
#include "Common/Player.h"
#include "Common/EngineLoader.h"
#include "Common/SetupManager.h"

#include "Control/ControlLayer.h"
#include "Control/IControl.h"
#include "Control/IControlLayerListener.h"

#include "Entities/EntityFactory.h"

#include "Graphics/Base/MaterialInfo.h"
#include "Graphics/Base/TextureArray.h"
#include "Graphics/Base/Mesh.h"
#include "Graphics/Base/Vertex.h"
#include "Graphics/Base/MeshDecorator/ConcreteMesh.h"
#include "Graphics/Base/MeshDecorator/DecoratorList.h"

#include "Graphics/Camera/ICamera.h"
#include "Graphics/Camera/CameraFP.h"
#include "Graphics/Camera/CameraTP.h"
#include "Graphics/Camera/CameraSpline.h"

#include "Graphics/FX/Fog.h"
#include "Graphics/FX/Light.h"
#include "Graphics/FX/Water.h"

#include "Graphics/Model/IModel.h"
#include "Graphics/Model/KFModel/KFModelFactory.h"
#include "Graphics/Model/Primitive/PrimitiveFactory.h"

#include "Graphics/Render/Drawer.h"
#include "Graphics/Render/DrawerOpenGL.h"
#include "Graphics/Render/enumDrawer.h"
#include "Graphics/Render/Frustum.h"
#include "Graphics/Render/RenderManager.h"

#include "Graphics/Toolkit/Button.h"
#include "Graphics/Toolkit/Label.h"
#include "Graphics/Toolkit/TextureDecorator.h"
#include "Graphics/Toolkit/Window.h"

#include "Graphics/World/IScene.h"
#include "Graphics/World/BspScene.h"
#include "Graphics/World/Heightmap/HeightmapBase.h"
#include "Graphics/World/Heightmap/HeightmapBruteForce.h"

#include "Math/Quaternion.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Spline.h"

#include "Network/NetControl.h"
#include "Network/NetClient.h"
#include "Network/NetCustomMessage.h"
#include "Network/NetServer.h"

/*#include "Physics/IBoundingVolumes.h"
#include "Physics/BoundingVolumes/BoundingBox.h"
#include "Physics/BoundingVolumes/BoundingSphere.h"
#include "Physics/PhysicsEnvironment.h"
#include "Physics/MoveCollisionInfo.h"*/

#include "Physics/PhysicsManager.h"
#include "Physics/PhysicalWorld.h"
#include "Physics/PhysicalBody.h"
#include "Physics/PhysicalGeom.h"
#include "Physics/PhysicalSpace.h"
#include "Physics/PhysicalJoint.h"
#include "Physics/PhysicalJointGroup.h"
#include "Physics/PhysicalContactPoint.h"

#include "Physics/Geoms/GeomBox.h"
#include "Physics/Geoms/GeomCylinder.h"
#include "Physics/Geoms/GeomPlane.h"
#include "Physics/Geoms/GeomRay.h"
#include "Physics/Geoms/GeomSphere.h"
#include "Physics/Geoms/GeomTriMesh.h"

#include "Physics/Joints/JointAMotor.h"
#include "Physics/Joints/JointBall.h"
#include "Physics/Joints/JointContact.h"
#include "Physics/Joints/JointFixed.h"
#include "Physics/Joints/JointHinge.h"
#include "Physics/Joints/JointHinge2.h"
#include "Physics/Joints/JointSlider.h"
#include "Physics/Joints/JointUniversal.h"

#include "Triggers/ITrigger.h"
#include "Triggers/TriggerManager.h"

#include "Util/BitSet.h"



#endif


