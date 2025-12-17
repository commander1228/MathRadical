import { ref } from 'vue';

export interface HistoryItem {
    a: string | number;
    b: string | number;
    result: string | number;
    operation: 'GCD' | 'LCM';
    timestamp: number;
}

const HISTORY_KEY = 'mathradical_history';
const MAX_ITEMS = 10;

export function useHistory() {
    const history = ref<HistoryItem[]>([]);

    // Load from local storage
    const loadHistory = () => {
        const stored = localStorage.getItem(HISTORY_KEY);
        if (stored) {
            try {
                history.value = JSON.parse(stored);
            } catch (e) {
                console.error('Failed to parse history', e);
                history.value = [];
            }
        }
    };

    // Save to local storage
    const saveHistory = () => {
        localStorage.setItem(HISTORY_KEY, JSON.stringify(history.value));
    };

    const addToHistory = (item: Omit<HistoryItem, 'timestamp'>) => {
        const newItem: HistoryItem = {
            ...item,
            timestamp: Date.now(),
        };

        // Add to beginning
        history.value.unshift(newItem);

        // Keep only last 10
        if (history.value.length > MAX_ITEMS) {
            history.value = history.value.slice(0, MAX_ITEMS);
        }

        saveHistory();
    };

    const clearHistory = () => {
        history.value = [];
        localStorage.removeItem(HISTORY_KEY);
    };

    // Load immediately on creation (or can be done in onMounted if preferred, 
    // but for a composable meant to be shared, calling it here ensures state is ready)
    loadHistory();

    return {
        history,
        addToHistory,
        clearHistory
    };
}
