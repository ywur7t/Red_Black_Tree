//Ключ - номер аудитории(1 поле - 1 буква, 2 поле - 3 цифры)
//КЧ, без повторов, 
//удаление(замена на минимальный справа), 
//7 - Сравнить два дерева по значению (два дерева равны, если содержат одинаковые элементы)

#include <iostream>
#include <tuple>


enum nodecolor { black, red };
struct nodekey//структура ключа
{
    char literal;
    int digit;
};
struct node//структура узла
{
    struct node* parent;
    nodecolor color;      nodekey key;
    struct node* left;    struct node* right;
};
node* tnull = new node();


void leftrotate(node*& root, node* x)
{
    node* y = x->right;
    x->right = y->left;

    if (y->left != tnull)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tnull)
        root = y;
    else
    {
        if (x == x->parent->left)
            x->parent->right = y;
        else x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void rightrotate(node*& root, node* x)
{
    node* y = x->left;
    x->left = y->right;

    if (y->right != tnull and y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == tnull and x->right != nullptr)
        root = y;
    else
    {
        if (x == x->parent->right)
            x->parent->left = y;
        else x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void draw(node* root, int h)//вывод дерева положеного на бок
{
    if (root != tnull)
    {
        draw(root->right, h + 4);
        for (auto i = 1; i <= h; i++)
            std::cout << " ";
        std::cout << root->key.literal << root->key.digit << " " << root->color << "\n";
        draw(root->left, h + 4);
    }


}

void rb_isert_fixup(node*& root, node* z)
{
    while (z->parent->color == red)
    {
        if (z->parent == z->parent->parent->left)
        {
            node* y = z->parent->parent->right;
            if (y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftrotate(root, z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                rightrotate(root, z->parent->parent);
            }
        }
        else
        {
            node* y = z->parent->parent->left;
            if (y->color == red)
            {
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightrotate(root, z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                leftrotate(root, z->parent->parent);
            }
        }
    }
    root->color = black;
}
void rb_insert(node*& root, nodekey* userkey)
{
    node* z = new node(); z->parent = nullptr; z->color = red; z->left = nullptr; z->right = nullptr; z->key.literal = userkey->literal; z->key.digit = userkey->digit;
    node* y = tnull;
    node* x = root;
    while (x != tnull and x != nullptr)
    {
        y = x;
        if (std::tie(z->key.literal, z->key.digit) < std::tie(x->key.literal, x->key.digit))
        {
            x = x->left;
        }
        else x = x->right;
    }
    z->parent = y;
    if (y == tnull)
        root = z;
    else

        if (std::tie(z->key.literal, z->key.digit) < std::tie(y->key.literal, y->key.digit))
        {
            y->left = z;
        }
        else

            y->right = z;
    z->left = tnull;
    z->right = tnull;
    z->color = red;
    root->parent = tnull;
    rb_isert_fixup(root, z);


}

node* search(node* x, nodekey* k)
{
    if (x == tnull or (std::tie(k->literal, k->digit) == std::tie(x->key.literal, x->key.digit)))
        return x;
    if (std::tie(k->literal, k->digit) < std::tie(x->key.literal, x->key.digit))
        return search(x->left, k);
    else return search(x->right, k);
}

void rb_delete_fixup(node*& root, node* x)
{
    while (x != root and x->color == black)
    {
        if (x == x->parent->left)
        {
            node* w = x->parent->right;
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                leftrotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black and w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == black)
                {
                    w->left->color = black;
                    w->color = red;
                    rightrotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftrotate(root, x->parent);
                x = root;
            }
        }
        else
        {
            node* w = x->parent->left;
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                rightrotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black and w->left->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == black)
                {
                    w->right->color = black;
                    w->color = red;
                    leftrotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightrotate(root, x->parent);
                x = root;
            }
        }
    }
    x->color = black;
}
node* tree_minimum(node* x)
{
    while (x->left != tnull)
        x = x->left;
    return x;
}
void rb_transplant(node*& root, node* u, node* v)
{
    if (u->parent == tnull)
        root = v;
    else
    {
        if (u == u->parent->left)
            u->parent->left = v;
        else u->parent->right = v;
    }
    v->parent = u->parent;
}
void rb_delete(node*& root, nodekey* userkey)
{
    node* z = search(root, userkey);
    if (z != tnull)
    {
        node* y = z; node* x = tnull;
        int y_original_color = y->color;
        if (z->left == tnull)
        {
            node* x = z->right;
            rb_transplant(root, z, z->right);
        }
        else
        {
            if (z->right == tnull)
            {
                 x = z->left;
                rb_transplant(root, z, z->left);
            }
            else
            {
                y = tree_minimum(z->right);
                y_original_color = y->color;
                 x = y->right;
                if (y->parent == z)
                    x->parent = y;
                else
                {
                    rb_transplant(root, y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                rb_transplant(root, z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }

        }
        if (y_original_color == black)
            rb_delete_fixup(root, x);
    }
}


bool inorder(node* first, node* second)//сравнение деревьев
{
    if (std::tie(first->key.literal, first->key.digit) == std::tie(second->key.literal, second->key.digit))
        return false;
    if (first != tnull and second != tnull)
        return inorder(first->left, second->left) && inorder(first->right, second->right);
}


void deletetree(node*& root)
{
    if (root != tnull)
    {
        deletetree(root->left);
        if (root->left != tnull)
            delete(root->left);

        deletetree(root->right);
        if (root->right != tnull)
            delete(root->right);
    }
    if (root->left == tnull and root->right == tnull) { delete(root); root = tnull; }

}

int main()
{
    node* first = nullptr;
    node* second = nullptr;
    nodekey* userkey = new nodekey();

    return 0;
}
