#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "react_render.h"

void check_path(const char *path, const char *expected) {
        char *buf;

        buf = render_path(path);
        ck_assert_msg(buf != NULL, "Expected <%s> to return a valid buffer", path);
        ck_assert_msg(strstr(buf, expected),
                      "Expected <%s> to contain %s, actually returned %s",
                      path, expected, buf);
        free(buf);
}

void check_element(const char *element, const char *props_as_json, const char *expected) {
        char *buf;

        buf = render_element(element, props_as_json);
        ck_assert_msg(buf != NULL, "Expected <%s> to return a valid buffer", element);
        ck_assert_msg(strstr(buf, expected),
                      "Expected <%s> with props %s to contain %s, actually returned %s",
                      element, props_as_json, expected, buf);
        free(buf);
}

START_TEST(test_render_404)
{
        check_path("/notfound", "404 :(");
}
END_TEST

START_TEST(test_render_root)
{
        check_path("/", "Hello Isomorphic React!");
}
END_TEST

START_TEST(test_render_snowman)
{
        check_element("UnicodeView", "{}", "☃");
}
END_TEST

START_TEST(test_render_snowman_with_no_props)
{
        check_element("UnicodeView", NULL, "☃");
}
END_TEST

START_TEST(test_render_snowman_closes_div_tag)
{
        check_element("UnicodeView", "{}", "</div>");
}
END_TEST

START_TEST(test_render_unknown_element)
{
        char *buf = render_element("UnknownElement", "{}");
        ck_assert_msg(buf == NULL, "Expected UnknownElement to return an invalid buffer");
}
END_TEST

START_TEST(test_render_with_props)
{
        check_element("PropsView", "{\"name\":\"Sarah\"}", "Sarah");
        check_element("PropsView", "{\"name\":\"Geoff\"}", "Geoff");
}
END_TEST

void render_path_setup()
{
        render_set_debug(1);
        render_init("../bundle.router.js");
}

void render_path_teardown()
{
        render_reset();
}

void render_element_setup()
{
        render_set_debug(1);
        render_init("../bundle.element.js");
}

void render_element_teardown()
{
        render_reset();
}

Suite * react_render_suite()
{
        Suite *s;
        TCase *tc_path, *tc_element;

        s = suite_create("React Rendering");

        tc_path = tcase_create("render path");
        tcase_add_checked_fixture(tc_path, render_path_setup, render_path_teardown);
        tcase_add_test(tc_path, test_render_404);
        tcase_add_test(tc_path, test_render_root);

        tc_element = tcase_create("render element");
        tcase_add_checked_fixture(tc_element, render_element_setup, render_element_teardown);
        tcase_add_test(tc_element, test_render_snowman);
        tcase_add_test(tc_element, test_render_snowman_with_no_props);
        tcase_add_test(tc_element, test_render_snowman_closes_div_tag);
        tcase_add_test(tc_element, test_render_unknown_element);
        tcase_add_test(tc_element, test_render_with_props);

        suite_add_tcase(s, tc_path);
        suite_add_tcase(s, tc_element);

        return s;
}

int main(void) {
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = react_render_suite();
        sr = srunner_create(s);

        render_set_debug(1);
        render_init("../bundle.router.js");

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
