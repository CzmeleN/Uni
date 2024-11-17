export const name = 'Module B';
export let aModName;

(async () => {
    const a = await import('./a.mjs')
    aModName = a.name;
})();
