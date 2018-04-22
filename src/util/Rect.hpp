#pragma once


class Rectf
{
public:
    Vector2f position;
    Vector2f size;

    //Comparison / relational operators
    bool operator ==(const Rectf& b) const { return (position == b.position) && (size == b.size); }
    bool operator !=(const Rectf& b) const { return !(*this == b); }

public:
    Rectf() { }
    Rectf(float nx, float ny, float nw, float nh) : position(nx, ny), size(nw, nh) { }
    Rectf(float nx, float ny, const Vector2f& nd) : position(nx, ny), size(nd) { }
    Rectf(const Vector2f& np, float nw, float nh) : position(np), size(nw, nh) { }
    Rectf(const Vector2f& np, const Vector2f& nd) : position(np), size(nd) { }

    bool contains(const Vector2f& newPt) const
    {
        return  newPt.x >= position.x &&
                newPt.y >= position.y &&
                newPt.x < (position.x + size.width) &&
                newPt.y < (position.y + size.height);
    }

    /**
     * stuff I added:
     */
    float left() { return this->position.x; }
    float right() { return this->position.x + this->size.x; }
    float top() { return this->position.y; }
    float bottom() { return this->position.y + this->size.y; }

    Vector2f center() { return this->position + this->size/2; }


    void log(const char *name)
    {
        printf("[%s]{ x: %f y: %f w: %f h: %f }\n",
            name,
            this->position.x,
            this->position.y,
            this->size.width,
            this->size.height
        );           
    }

    
    // taken from: https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
    static bool collides(Rectf a, Rectf b)
    {
        return (
            a.position.x < b.position.x + b.size.width &&
            a.position.x + a.size.width > b.position.x &&
            a.position.y < b.position.y + b.size.height &&
            a.size.height + a.position.y > b.position.y
        );
    }

    static Rectf intersection(Rectf a, Rectf b)
    {
        float ax0 = a.left();
        float ax1 = a.right();
        float ay0 = a.top();
        float ay1 = a.bottom();    
        
        float bx0 = b.left();
        float bx1 = b.right();
        float by0 = b.top();
        float by1 = b.bottom();    

        float x0 = ax0 >= bx0 ? ax0 : bx0;
        float y0 = ay0 >= by0 ? ay0 : by0;
        

        float x1 = ax1 <= bx1 ? ax1 : bx1;
        float y1 = ay1 <= by1 ? ay1 : by1;

        return Rectf(
            x0,
            y0,
            x1 - x0,
            y1 - y0
        );
    }
    
};
