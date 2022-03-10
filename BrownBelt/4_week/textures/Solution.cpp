#include "Common.h"

using namespace std;

Size GetSize_common(const Image& image) 
{
    auto width = static_cast<int>(image.empty() ? 0 : image[0].size());
    auto height = static_cast<int>(image.size());
    return {width, height};
}

bool Is_Collide_point(Point _point, Size _size) 
{
    return  _point.x >= 0 && 
            _point.x < _size.width && 
            _point.y >= 0 && 
            _point.y < _size.height;
}


class Shaper : public IShape {
public:
    virtual void SetPosition(Point point_) override 
    {
        point = point_;
    }
    virtual Point GetPosition() const override 
    {
        return point;
    }

    virtual void SetSize(Size size_) override 
    {
        size = size_;
    }
    virtual Size GetSize() const override 
    {
        return size;
    }

    virtual void SetTexture(shared_ptr<ITexture> texture_) override 
    {
        texture = move(texture_);
    }
    virtual ITexture* GetTexture() const override 
    {
        return texture.get();
    }
    virtual bool Is_Collide(Point) const = 0;

    virtual void Draw(Image& image) const override 
    {
        auto image_size = GetSize_common(image);
        Point temp_point;
        for (temp_point.y = 0; temp_point.y < size.height; temp_point.y++) 
        {
            for (temp_point.x = 0; temp_point.x < size.width; temp_point.x++) 
            {
                if (Is_Collide(temp_point)) 
                {
                    char pict = '.';
                    if (texture && Is_Collide_point(temp_point, texture->GetSize())) 
                    {
                        pict = texture->GetImage()[temp_point.y][temp_point.x];
                    }
                    Point temp = {point.x + temp_point.x, point.y + temp_point.y};
                    if (Is_Collide_point(temp, image_size)) 
                    {
                        image[temp.y][temp.x] = pict;
                    }
                }
            }
        }
    }

protected:
    Point point;
    Size size;
    shared_ptr<ITexture> texture;
};

class IRectangle : public Shaper {
public:
    unique_ptr<IShape> Clone() const override 
    {
        return make_unique<IRectangle>(*this);
    }

private:
    bool Is_Collide(Point) const override 
    {
        return true;
    }
};

class IEllipse : public Shaper {
public:
    unique_ptr<IShape> Clone() const override 
    {
        return make_unique<IEllipse>(*this);
    }

private:
    bool Is_Collide(Point _point) const override 
    {
        return IsPointInEllipse(_point, GetSize());
    }
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) 
{
    switch (shape_type) 
    {
        case ShapeType::Rectangle: return make_unique<IRectangle>(); break;
        case ShapeType::Ellipse:   return make_unique<IEllipse>(); break;
    }
    return nullptr;
}