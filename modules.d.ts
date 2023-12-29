declare module "modules" {
  declare function hello(): string;
  declare function index(): string;
  declare function about(): string;
  declare function favicon(): string;
  declare function icon512x512(): string;
  declare function add(a: number, b: number): number;
}
declare module "hostconfig:modules" {
  export * from "modules";
}
