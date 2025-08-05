import { writable } from "svelte/store";
import { User } from "../lib/User.js";

export const currUser = writable<User | null>(new User('', '', '', ''));