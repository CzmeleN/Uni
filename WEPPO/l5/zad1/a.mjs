export const name = 'Module A';
export let bModName;

(async () => {
    const b = await import('./b.mjs')
    bModName = b.name;
})();
