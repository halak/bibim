namespace Bibim
{
    void CollisionSpace2D::Clear()
    {
        shapes.clear();
    }

    void CollisionSpace2D::Clear(int group)
    {
        shapes.at(group).clear();
    }

    int CollisionSpace2D::GetNumberOfGroups() const
    {
        return static_cast<int>(shapes.size());
    }

    bool CollisionSpace2D::GetCollisionRelationship(int groupA, int groupB) const
    {
        return collisionRelationships.at(groupA).at(groupB);
    }

    void CollisionSpace2D::SetCollisionRelationship(int groupA, int groupB, bool detectable)
    {
        collisionRelationships.at(groupA).at(groupB) = detectable;
        collisionRelationships.at(groupB).at(groupA) = detectable;
    }

    const CollisionSpace2D::ShapeCollection& CollisionSpace2D::GetShapes(int group) const
    {
        return shapes.at(group);
    }
}