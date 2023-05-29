#include <gtest/gtest.h>

extern "C" {
#include <list.h>
}

int node_data(Node* const node)
{
    return *((int*)node_data_get(node));
}

void int_copy(void* const dest, const void* const source)
{
    memcpy(dest, source, sizeof(int));
}

void int_dtor(void* const ptr) {;}

List* list_construct_int(void)
{
    return list_construct(sizeof(int), int_copy, int_dtor);
}

Node* list_push_front_int(List* const list, int push)
{
    return list_push_front(list, &push);
}

Node* list_push_back_int(List* const list, int push)
{
    return list_push_back(list, &push);
}

Node* list_insert_after_int(List* const list, Node* const node, int push)
{
    return list_insert_after(list, node, &push);
}

TEST(List, list_construct)
{
    List* list = list_construct_int();

    EXPECT_EQ(list_size(list), 0);
    EXPECT_EQ(list_head(list), nullptr);
    EXPECT_EQ(list_const_head(list), nullptr);
    EXPECT_EQ(list_tail(list), nullptr);
    EXPECT_EQ(list_const_tail(list), nullptr);

    list_destruct(list);
}

TEST(List, list_push_front)
{
    List* list = list_construct_int();
    Node* node = list_push_front_int(list, 1);

    Node* head = list_head(list);
    Node* tail = list_tail(list);

    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(head, node);
    EXPECT_NE(head, nullptr);
    EXPECT_NE(list_const_head(list), nullptr);
    EXPECT_NE(tail, nullptr);
    EXPECT_NE(list_const_tail(list), nullptr);
    EXPECT_EQ(head, tail);
    EXPECT_EQ(node_data(head), 1);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    node = list_push_front_int(list, -1);

    Node* head1 = list_head(list);
    Node* tail1 = list_tail(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(head1, node);
    EXPECT_NE(head1, nullptr);
    EXPECT_NE(tail1, nullptr);
    EXPECT_NE(head1, tail1);
    EXPECT_EQ(tail1, tail);
    EXPECT_EQ(node_data(head1), -1);
    EXPECT_EQ(node_data(tail1), 1);
    EXPECT_EQ(node_next(head1), tail1);
    EXPECT_EQ(node_prev(head1), nullptr);
    EXPECT_EQ(node_next(tail1), nullptr);
    EXPECT_EQ(node_prev(tail1), head1);

    node = list_push_front_int(list, -2);

    Node* head2 = list_head(list);
    Node* tail2 = list_tail(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_EQ(head2, node);
    EXPECT_NE(head2, nullptr);
    EXPECT_NE(tail2, nullptr);
    EXPECT_NE(head2, tail2);
    EXPECT_EQ(tail2, tail1);
    EXPECT_EQ(node_data(head2), -2);
    EXPECT_EQ(node_data(tail2), 1);
    EXPECT_EQ(node_next(node_next(head2)), tail2);
    EXPECT_EQ(node_data(node_next(head2)), -1);
    EXPECT_EQ(node_prev(node_prev(tail2)), head2);

    list_destruct(list);
}

TEST(List, list_push_back)
{
    List* list = list_construct_int();
    Node* node = list_push_back_int(list, 1);

    Node* head = list_head(list);
    Node* tail = list_tail(list);

    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(node, tail);
    EXPECT_NE(head, nullptr);
    EXPECT_NE(list_const_head(list), nullptr);
    EXPECT_NE(tail, nullptr);
    EXPECT_NE(list_const_tail(list), nullptr);
    EXPECT_EQ(head, tail);
    EXPECT_EQ(node_data(head), 1);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    node = list_push_back_int(list, 2);

    Node* head1 = list_head(list);
    Node* tail1 = list_tail(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(node, tail1);
    EXPECT_NE(head1, nullptr);
    EXPECT_NE(tail1, nullptr);
    EXPECT_NE(head1, tail1);
    EXPECT_EQ(head1, head);
    EXPECT_EQ(node_data(head1), 1);
    EXPECT_EQ(node_data(tail1), 2);
    EXPECT_EQ(node_next(head1), tail1);
    EXPECT_EQ(node_prev(head1), nullptr);
    EXPECT_EQ(node_next(tail1), nullptr);
    EXPECT_EQ(node_prev(tail1), head1);

    node = list_push_back_int(list, 3);

    Node* head2 = list_head(list);
    Node* tail2 = list_tail(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_EQ(node, tail2);
    EXPECT_NE(head2, nullptr);
    EXPECT_NE(tail2, nullptr);
    EXPECT_NE(head2, tail2);
    EXPECT_EQ(head2, head1);
    EXPECT_EQ(node_data(head2), 1);
    EXPECT_EQ(node_data(tail2), 3);
    EXPECT_EQ(node_next_n(head2, 2), tail2);
    EXPECT_EQ(node_data(node_next(head2)), 2);
    EXPECT_EQ(node_prev_n(tail2, 2), head2);

    list_destruct(list);
}

TEST(List, list_insert_after)
{
    List* list = list_construct_int();
    list_push_back_int(list, 10);
    list_push_back_int(list, 20);
    list_push_back_int(list, 30);
    list_push_back_int(list, 40);
    list_push_back_int(list, 50);

    Node* node = list_insert_after_int(list, NULL, 0);

    EXPECT_EQ(list_size(list), 6);
    EXPECT_EQ(node, list_head(list));
    EXPECT_EQ(node_data(node_next(node)), 10);
    EXPECT_EQ(node_prev(node_next(node)), node);
    EXPECT_EQ(node_prev(node), nullptr);

    Node* ins_node = node_next_n(list_head(list), 2);
    node = list_insert_after_int(list, ins_node, 25);

    EXPECT_EQ(list_size(list), 7);
    EXPECT_EQ(node, node_next_n(list_head(list), 3));
    Node* prev = node_prev(node);
    Node* next = node_next(node);
    EXPECT_EQ(node_data(prev), 20);
    EXPECT_EQ(node_data(next), 30);
    EXPECT_EQ(node_next(prev), node);
    EXPECT_EQ(node_prev(next), node);

    node = list_insert_after_int(list, list_tail(list), 60);

    EXPECT_EQ(list_size(list), 8);
    EXPECT_EQ(node_data(node), 60);
    EXPECT_EQ(node, list_tail(list));
    EXPECT_EQ(node_data(node_prev(node)), 50);
    EXPECT_EQ(node_next(node_prev(node)), node);
    EXPECT_EQ(node_next(node), nullptr);

    list_destruct(list);
}

TEST(List, list_erase)
{
    List* list = list_construct_int();
    list_push_back_int(list, 10); // 0
    list_push_back_int(list, 20); // 1
    list_push_back_int(list, 30); // 2
    list_push_back_int(list, 40); // 3
    list_push_back_int(list, 50); // 4

    Node* head = list_head(list);
    Node* tail = list_tail(list);

    EXPECT_EQ(list_size(list), 5);

    Node* erase_node = node_next_n(list_head(list), 2);
    list_erase(list, erase_node);

    EXPECT_EQ(list_size(list), 4);

    EXPECT_EQ(list_head(list), head);
    EXPECT_EQ(list_tail(list), tail);
    Node* twenty = node_next(list_head(list));
    Node* fourty = node_prev(list_tail(list));
    EXPECT_EQ(node_data(twenty), 20);
    EXPECT_EQ(node_data(fourty), 40);
    EXPECT_EQ(node_next(twenty), fourty);
    EXPECT_EQ(node_prev(fourty), twenty);

    list_pop_back(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_NE(list_tail(list), tail);
    EXPECT_EQ(list_head(list), head);
    tail = list_tail(list);
    EXPECT_EQ(node_next(tail), nullptr);
    EXPECT_EQ(node_data(tail), 40);
    EXPECT_EQ(node_data(node_prev(tail)), 20);
    EXPECT_EQ(node_next(node_prev(tail)), tail);

    list_pop_front(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(list_tail(list), tail);
    EXPECT_NE(list_head(list), head);
    head = list_head(list);
    EXPECT_EQ(node_prev(head), nullptr);
    EXPECT_EQ(node_data(head), 20);
    EXPECT_EQ(node_data(node_next(head)), 40);
    EXPECT_EQ(node_prev(node_next(head)), head);

    list_pop_back(list);
    
    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(list_head(list), list_tail(list));
    EXPECT_EQ(list_head(list), head);
    EXPECT_NE(list_tail(list), tail);
    EXPECT_EQ(node_data(head), 20);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    list_pop_back(list);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_EQ(list_head(list), nullptr);
    EXPECT_EQ(list_tail(list), nullptr);

    list_destruct(list);
}

void list_copy_for_ctor(void* const dest, const void* const source)
{
    *((List**)dest) = list_copy(*((List**)source));
}

void list_dtor_for_ctor(void* const ptr)
{
    list_destruct(*((List**)ptr));
}

Node* list_push_back_tmp_list(List* const list, List* const push)
{
    Node* ret = list_push_back(list, &push);
    list_destruct(push);
    return ret;
}

List* list_get(Node* const node)
{
    return *((List**)node_data_get(node));
}

TEST(List, type_erasure)
{
    List* list = list_construct(sizeof(List*), list_copy_for_ctor, list_dtor_for_ctor);

    Node* arr[5] = {};

    for (int i = 0; i < 5; i++)
    {
        arr[i] = list_push_back_tmp_list(list, list_construct_int());
        for (int j = 0; j < 100; j++)
            list_push_back_int(list_get(arr[i]), j);
    }

    List* ilist = list_construct_int();
    for (int i = 0; i < 1000; i++)
        list_push_back_int(ilist, i);

    list_push_back(list, &ilist);

    for (int i = 0; i < 5; i++)
        for (auto j = 0; j < 100; j++)
            EXPECT_EQ(j, node_data(node_next_n(list_head(list_get(node_next_n(list_head(list), i))), j)));

    for (int i = 0; i < 1000; i++)
        EXPECT_EQ(i, node_data(node_next_n(list_head(list_get(node_next_n(list_head(list), 5))), i)));

    list_destruct(list);
    list_destruct(ilist);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}