#include <gtest/gtest.h>

extern "C" {
#include <list.h>
}

TEST(List, list_construct)
{
    List* list = list_construct();

    EXPECT_EQ(list_size(list), 0);
    EXPECT_EQ(list_head(list), nullptr);
    EXPECT_EQ(list_const_head(list), nullptr);
    EXPECT_EQ(list_tail(list), nullptr);
    EXPECT_EQ(list_const_tail(list), nullptr);

    list_destruct(list);
}

TEST(List, list_push_front)
{
    List* list = list_construct();
    Node* node = list_push_front(list, 1);

    Node* head = list_head(list);
    Node* tail = list_tail(list);

    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(head, node);
    EXPECT_NE(head, nullptr);
    EXPECT_NE(list_const_head(list), nullptr);
    EXPECT_NE(tail, nullptr);
    EXPECT_NE(list_const_tail(list), nullptr);
    EXPECT_EQ(head, tail);
    EXPECT_EQ(node_data_get(head), 1);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    node = list_push_front(list, -1);

    Node* head1 = list_head(list);
    Node* tail1 = list_tail(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(head1, node);
    EXPECT_NE(head1, nullptr);
    EXPECT_NE(tail1, nullptr);
    EXPECT_NE(head1, tail1);
    EXPECT_EQ(tail1, tail);
    EXPECT_EQ(node_data_get(head1), -1);
    EXPECT_EQ(node_data_get(tail1), 1);
    EXPECT_EQ(node_next(head1), tail1);
    EXPECT_EQ(node_prev(head1), nullptr);
    EXPECT_EQ(node_next(tail1), nullptr);
    EXPECT_EQ(node_prev(tail1), head1);

    node = list_push_front(list, -2);

    Node* head2 = list_head(list);
    Node* tail2 = list_tail(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_EQ(head2, node);
    EXPECT_NE(head2, nullptr);
    EXPECT_NE(tail2, nullptr);
    EXPECT_NE(head2, tail2);
    EXPECT_EQ(tail2, tail1);
    EXPECT_EQ(node_data_get(head2), -2);
    EXPECT_EQ(node_data_get(tail2), 1);
    EXPECT_EQ(node_next(node_next(head2)), tail2);
    EXPECT_EQ(node_data_get(node_next(head2)), -1);
    EXPECT_EQ(node_prev(node_prev(tail2)), head2);

    list_destruct(list);
}

TEST(List, list_push_back)
{
    List* list = list_construct();
    Node* node = list_push_back(list, 1);

    Node* head = list_head(list);
    Node* tail = list_tail(list);

    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(node, tail);
    EXPECT_NE(head, nullptr);
    EXPECT_NE(list_const_head(list), nullptr);
    EXPECT_NE(tail, nullptr);
    EXPECT_NE(list_const_tail(list), nullptr);
    EXPECT_EQ(head, tail);
    EXPECT_EQ(node_data_get(head), 1);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    node = list_push_back(list, 2);

    Node* head1 = list_head(list);
    Node* tail1 = list_tail(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(node, tail1);
    EXPECT_NE(head1, nullptr);
    EXPECT_NE(tail1, nullptr);
    EXPECT_NE(head1, tail1);
    EXPECT_EQ(head1, head);
    EXPECT_EQ(node_data_get(head1), 1);
    EXPECT_EQ(node_data_get(tail1), 2);
    EXPECT_EQ(node_next(head1), tail1);
    EXPECT_EQ(node_prev(head1), nullptr);
    EXPECT_EQ(node_next(tail1), nullptr);
    EXPECT_EQ(node_prev(tail1), head1);

    node = list_push_back(list, 3);

    Node* head2 = list_head(list);
    Node* tail2 = list_tail(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_EQ(node, tail2);
    EXPECT_NE(head2, nullptr);
    EXPECT_NE(tail2, nullptr);
    EXPECT_NE(head2, tail2);
    EXPECT_EQ(head2, head1);
    EXPECT_EQ(node_data_get(head2), 1);
    EXPECT_EQ(node_data_get(tail2), 3);
    EXPECT_EQ(node_next_n(head2, 2), tail2);
    EXPECT_EQ(node_data_get(node_next(head2)), 2);
    EXPECT_EQ(node_prev_n(tail2, 2), head2);

    list_destruct(list);
}

TEST(List, list_insert_after)
{
    List* list = list_construct();
    list_push_back(list, 10);
    list_push_back(list, 20);
    list_push_back(list, 30);
    list_push_back(list, 40);
    list_push_back(list, 50);

    Node* node = list_insert_after(list, NULL, 0);

    EXPECT_EQ(list_size(list), 6);
    EXPECT_EQ(node, list_head(list));
    EXPECT_EQ(node_data_get(node_next(node)), 10);
    EXPECT_EQ(node_prev(node_next(node)), node);
    EXPECT_EQ(node_prev(node), nullptr);

    Node* ins_node = node_next_n(list_head(list), 2);
    node = list_insert_after(list, ins_node, 25);

    EXPECT_EQ(list_size(list), 7);
    EXPECT_EQ(node, node_next_n(list_head(list), 3));
    Node* prev = node_prev(node);
    Node* next = node_next(node);
    EXPECT_EQ(node_data_get(prev), 20);
    EXPECT_EQ(node_data_get(next), 30);
    EXPECT_EQ(node_next(prev), node);
    EXPECT_EQ(node_prev(next), node);

    node = list_insert_after(list, list_tail(list), 60);

    EXPECT_EQ(list_size(list), 8);
    EXPECT_EQ(node_data_get(node), 60);
    EXPECT_EQ(node, list_tail(list));
    EXPECT_EQ(node_data_get(node_prev(node)), 50);
    EXPECT_EQ(node_next(node_prev(node)), node);
    EXPECT_EQ(node_next(node), nullptr);

    list_destruct(list);
}

TEST(List, list_erase)
{
    List* list = list_construct();
    list_push_back(list, 10); // 0
    list_push_back(list, 20); // 1
    list_push_back(list, 30); // 2
    list_push_back(list, 40); // 3
    list_push_back(list, 50); // 4

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
    EXPECT_EQ(node_data_get(twenty), 20);
    EXPECT_EQ(node_data_get(fourty), 40);
    EXPECT_EQ(node_next(twenty), fourty);
    EXPECT_EQ(node_prev(fourty), twenty);

    list_pop_back(list);

    EXPECT_EQ(list_size(list), 3);
    EXPECT_NE(list_tail(list), tail);
    EXPECT_EQ(list_head(list), head);
    tail = list_tail(list);
    EXPECT_EQ(node_next(tail), nullptr);
    EXPECT_EQ(node_data_get(tail), 40);
    EXPECT_EQ(node_data_get(node_prev(tail)), 20);
    EXPECT_EQ(node_next(node_prev(tail)), tail);

    list_pop_front(list);

    EXPECT_EQ(list_size(list), 2);
    EXPECT_EQ(list_tail(list), tail);
    EXPECT_NE(list_head(list), head);
    head = list_head(list);
    EXPECT_EQ(node_prev(head), nullptr);
    EXPECT_EQ(node_data_get(head), 20);
    EXPECT_EQ(node_data_get(node_next(head)), 40);
    EXPECT_EQ(node_prev(node_next(head)), head);

    list_pop_back(list);
    
    EXPECT_EQ(list_size(list), 1);
    EXPECT_EQ(list_head(list), list_tail(list));
    EXPECT_EQ(list_head(list), head);
    EXPECT_NE(list_tail(list), tail);
    EXPECT_EQ(node_data_get(head), 20);
    EXPECT_EQ(node_next(head), nullptr);
    EXPECT_EQ(node_prev(head), nullptr);

    list_pop_back(list);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_EQ(list_head(list), nullptr);
    EXPECT_EQ(list_tail(list), nullptr);

    list_destruct(list);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}