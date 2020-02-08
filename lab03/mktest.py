#!/usr/bin/python
import sys
from random import choice, randint
from string import ascii_uppercase as upper


def get_random_key():
    return ''.join(choice(upper) for i in range(randint(1, 20)))


def main():
    if len(sys.argv) != 2:
        print("Usage: {0} <size of test>".format(
            sys.argv[0]))
        sys.exit(1)

    actions = [*["+"]*10, *["-"]*10, "?", "!"]
    acts_file = ["Load", "Save"]
    keys = {}
    test_file_name = "tests/"+sys.argv[1]
    with open("{0}.t".format(test_file_name), 'w') as output_file:
        for _ in range(int(sys.argv[1])):
            action = choice(actions)
            if action == "+":
                output_file.write(
                    "+ {0} {1}\n".format(get_random_key(), randint(1, 2**64-1)))

            elif action == "?":
                key = choice([key for key in keys.keys()]) if choice([True, False]) and len(
                    keys.keys()) > 0 else get_random_key()
                output_file.write("{0}\n".format(key))

            elif action == "-":
                output_file.write("- {0}\n".format(get_random_key()))

            elif action == "!":
                output_file.write("! {0} {1}\n".format(
                    choice(acts_file), '/ram/test'))

        output_file.close()


if __name__ == "__main__":
    sys.exit(main())
