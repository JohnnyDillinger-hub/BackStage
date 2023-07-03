#ifndef BACKGROUND_NODE_H
#define BACKGROUND_NODE_H

#include "SceneNode.h"

class Scene;

/*
    A SceneNode dedicated to rendering backgrounds. Defines a custom CalculateModel()
    function to ignore positional and rotational transformations. Can be extended to
    include/render 2D parallax maps.
*/
class BackgroundNode : public SceneNode
{
public:
    BackgroundNode(unsigned int ActorID);

    // calculates the model matrix for the background node, ignoring positions and rotations
    virtual void CalculateModel();
    // initializes the background node
    virtual void Initialize(Scene *scene);
    // renders the background node
    virtual void Render(Scene *scene, Renderer *renderer);
};
#endif