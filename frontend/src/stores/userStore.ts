import { writable } from "svelte/store";
import type { User } from "../lib/User.ts";

export const currUser = writable<User | null>(null);